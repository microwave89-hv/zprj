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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/protocol.h $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 2/11/14 8:10p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/protocol.h $
// 
// 12    2/11/14 8:10p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 11    9/13/13 2:02p Premkumara
// Uploaded back for EIP-128665 after TSEBootOnly 1240 release
// Files - Protocol.c, Protocol.h, AMIPostMgr.h
// 
// 10    8/26/13 2:15a Premkumara
// Reverted back for labelling BootOnly1240
// 
// 8     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     11/10/11 7:21p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// Added new parameter to the function prototype DISPLAY_TEXT_KEY_VALIDATE
// 
// 6     9/29/11 7:02p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 5     11/16/10 8:57a Mallikarjunanv
// [TAG] - EIP 41838  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Update AMI Post Manager Protocol witht he following. 2.
// Updating the interface PostManagerDisplayPostMessageEx to handle the
// cursor position properly. 2. Need to add new interface to GetAttribute
// [Rootcause] - 1. Display string is over written by the next string if
// the interface PostManagerDisplayPostMessageEx used simultaneously. 2.
// Need to get the attribute info to use PostManagerDisplayPostMessage
// interfaces effectively
// [Solution]- Fix in string.c to handle cursor and line positions. The
// files Protocol.c, Protocol.h and AmiPostMgr.h have the new interface
// implementaion to get the attribute.
// [Files] - Protocol.c, Protocol.h, AmiPostMgr.h and string.c
// 
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 4     2/04/10 12:03p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     2/05/09 5:19p Madhans
// PostMgrStatus interface added.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

#ifndef _PROTOCOL_H_
#define	_PROTOCOL_H_

EFI_STATUS InstallProtocol( VOID );
VOID UninstallProtocol( VOID );
EFI_STATUS PostManagerHandshake( VOID );
EFI_STATUS PostManagerSetCursorPosition(UINTN X, UINTN Y);
EFI_STATUS PostManagerGetCursorPosition(UINTN *pX, UINTN *pY);
EFI_STATUS PostManagerSetProgressBarPosition();
EFI_STATUS PostManagerInitProgressBar(
	UINTN x,
	UINTN y,
	UINTN w,
	UINTN h,
	UINTN delta);

TSE_POST_STATUS	PostManagerGetPostStatus(VOID);

EFI_STATUS PostManagerDisplayInfoBox(	CHAR16		*InfoBoxTitle,
										CHAR16		*InfoString,
										UINTN		Timeout,
										EFI_EVENT	*Event
						 			);


EFI_STATUS PostManagerSetAttribute(UINT8 ATTRIB);
EFI_STATUS PostManagerGetAttribute(UINT8 *ATTRIB);	//EIP-41838: new interface to get the attribute

EFI_STATUS
PostManagerDisplayMenu(
    IN VOID	*HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN UINT16 	LegendToken,	  
    IN POSTMENU_TEMPLATE *MenuData,
    IN UINT16 	MenuCount,
    OUT UINT16  *pSelection
);

typedef 
BOOLEAN
(EFIAPI *DISPLAY_TEXT_KEY_VALIDATE) (
	UINT16 ItemIndex,
    UINT16 Unicode,
    CHAR16	*Value
);


EFI_STATUS
PostManagerDisplayTextBox(
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE DisplayTextKeyValidate
);

EFI_STATUS PostManagerDisplayProgress (
IN UINT8		ProgressBoxState, 
IN CHAR16		*Title,
IN CHAR16		*Message,
IN CHAR16		*Legend,
IN UINTN 		Percent,	// 0 - 100
IN OUT VOID		**Handle,	//Out HANDLE. Valid Handle for update and close
OUT AMI_POST_MGR_KEY	*OutKey		//Out Key	   
);
#endif /* _PROTOCOL_H_ */


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
