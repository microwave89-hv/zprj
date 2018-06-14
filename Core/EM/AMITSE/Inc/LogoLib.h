//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 1985-2012, American Megatrends, Inc.   **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/LogoLib.h $
//
// $Author: Arunsb $
//
// $Revision: 10 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/LogoLib.h $
// 
// 10    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 9     2/02/12 12:40a Premkumara
// [TAG]  		EIP75136 
// [Category]  	New Feature
// [Description]  	Generic support for logos in RomHoles
// [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h
// 
// 8     1/31/12 1:18p Premkumara
// [TAG]  		EIP75136 
// [Category]  	New Feature
// [Description]  	Generic support for logos in RomHoles
// [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h,
// Postmgmt.c, AMILogo.h
// 
// 7     9/29/11 7:00p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 6     6/22/11 9:17a Premkumara
// [TAG]  		EIP60048
// [Category]  	Improvement
// [Description]  	TSE should Change the System Resolution according to
// the Quite Logo Size
// [Files]  		CommonHelper.c, AMITSE.sdl, Logo.c, LogoLib.h
// 
// 5     6/13/11 12:29p Rajashakerg
// [TAG]  		EIP60910 
// [Category]  	New Feature
// [Description]  	PNG image support in TSE.
// [Files]  		LogoLib.h, AMITSE.sdl, CommonHelper.c, logo.c, png.c, png.h,
// pnguncmp.c, TseAdvanced.cif
// 
// 4     4/16/10 5:11p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 4     2/04/10 12:01p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 3     8/13/09 12:09p Blaines
// Move Image support to binary module
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards.
// 
// 1     6/09/09 9:53a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:50p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		logolib.h
//
// Description:	logo related header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _LOGOLIB_H_
#define _LOGOLIB_H_

//OEM_POST Logo GUID. Don't change the GUID. ChangeLogo expects this GUID.
#define AMI_OEM_LOGO_GUID \
	{ 0x294b1cef, 0x9beb, 0x42d5, 0x99, 0x71, 0x0c, 0x89, 0x63, 0xcd, 0xaf, 0x02}

typedef enum { 
	BMP_Logo, 
	GIF_Logo, 
	JPEG_Logo,
	PCX_Logo,
	PNG_Logo,
	OEM_Format_LOGO,
    Unsupported_Logo
} LOGO_TYPE;

EFI_STATUS SetScreenResolution(UINTN ResX, UINTN ResY);
EFI_STATUS GetScreenResolution(UINTN *ResX, UINTN *ResY);
EFI_STATUS GOPSetScreenResolution(UINTN *Width, UINTN *Height);
EFI_STATUS GOPSetScreenResolutionHook(UINTN *Width, UINTN *Height, UINT32 Index);

EFI_STATUS
GetGraphicsBitMapFromFV ( 
IN EFI_GUID *FileNameGuid,
IN OUT VOID **Image,
IN OUT UINTN *ImageSize
);

EFI_STATUS
DrawImage( 
IN UINT8 *ImageData,
IN UINTN ImageSize,
IN CO_ORD_ATTRIBUTE Attribute,
IN INTN CoOrdX,
IN INTN CoOrdY,
IN BOOLEAN AdjustScreenResolution,
OUT UINTN *Width,
OUT UINTN *Height
);

EFI_STATUS PostManagerDisplayPostMessage( CHAR16 *message );
EFI_STATUS PostManagerDisplayPostMessageEx( CHAR16 *message, UINTN Attribute );
EFI_STATUS PostManagerSwitchToPostScreen( VOID );

EFI_STATUS
PostManagerDisplayMsgBox(
    IN CHAR16  *MsgBoxTitle,
    IN CHAR16  *Message,
    IN UINT8   MsgBoxType,
    OUT UINT8  *MsgBoxSel
);

EFI_STATUS
PostManagerDisplayTextBox(
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE DisplayTextKeyValidate
);

EFI_STATUS
PostManagerDisplayProgress(
IN UINT8	ProgressBoxState, 
IN CHAR16	*Title,
IN CHAR16	*Message,
IN CHAR16	*Legend,
IN UINTN 	Percent,	// 0 - 100
IN OUT VOID	**Handle,	//Out HANDLE. Valid Handle for update and close
OUT AMI_POST_MGR_KEY	*OutKey	//Out Key    
);

EFI_STATUS
PostManagerDisplayMsgBoxEx(
    IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,
    IN MSGBOX_EX_CATAGORY	 MsgBoxExCatagory,
    IN UINT8	 		MsgBoxType,
    IN UINT16			*OptionPtrTokens,	// Valid only with MSGBOX_TYPE_CUSTOM 
    IN UINT16	 		OptionCount,		// Valid only with MSGBOX_TYPE_CUSTOM
    IN AMI_POST_MGR_KEY		*HotKeyList, 		// NULL - AnyKeyPress closes
    IN UINT16 			HotKeyListCount, 
    OUT UINT8			*MsgBoxSel,
    OUT AMI_POST_MGR_KEY	*OutKey
);

EFI_STATUS
PostManagerDisplayQuietBootMessage(
    CHAR16 *Message,
    INTN CoOrdX,
    INTN CoOrdY,
    CO_ORD_ATTRIBUTE Attribute,
    EFI_UGA_PIXEL Foreground,
    EFI_UGA_PIXEL Background
);

EFI_STATUS PostManagerDisplayInfoBox(	CHAR16		*InfoBoxTitle,
										CHAR16		*InfoString,
										UINTN		Timeout,
										EFI_EVENT	*Event
						 			);

EFI_STATUS PostManagerSetCursorPosition(UINTN X, UINTN Y);
EFI_STATUS PostManagerGetCursorPosition(UINTN *pX, UINTN *pY);
EFI_STATUS PostManagerSetAttribute(UINT8 ATTRIB);
VOID  CleanUpLogo( VOID );

VOID InitPostScreen( VOID );

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2012, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
