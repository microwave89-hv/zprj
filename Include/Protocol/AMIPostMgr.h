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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Include/Protocol/AMIPostMgr.h $
//
// $Author: Arunsb $
//
// $Revision: 15 $
//
// $Date: 5/02/14 6:16a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Include/Protocol/AMIPostMgr.h $
// 
// 15    5/02/14 6:16a Arunsb
// [TAG]  		EIP128665
// [Category]  	Improvement
// [Description]  	Providing support to invalidate the BGRT status bit.
// [Files]  		protocol.c and amivfr.h
// 
// 14    2/11/14 7:29p Arunsb
// Reverted the changes for 2.16.1243 label
// 
// 13    9/13/13 2:04p Premkumara
// Uploaded back for EIP-128665 after TSEBootOnly 1240 release
// Files - Protocol.c, Protocol.h, AMIPostMgr.h
// 
// 12    8/26/13 2:18a Premkumara
// Reverted back for BootOnly1240 release
// 
// 10    10/18/12 5:44a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:24p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 9     11/10/11 7:17p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// Added new parameter to the function prototype DISPLAY_TEXT_KEY_VALIDATE
// 
// 8     9/29/11 7:00p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 7     12/02/10 12:10p Madhans
// [TAG] - EIP 41838  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Update AMI Post Manager Protocol witht he following. 2.
// Updating the interface PostManagerDisplayPostMessageEx to handle the
// cursor position properly. 2. Need to add new interface to GetAttribute
// To keep the GetAttribute to end of protocol.
// [Rootcause] - 1. Display string is over written by the next string if
// the interface PostManagerDisplayPostMessageEx used simultaneously. 2.
// Need to get the attribute info to use PostManagerDisplayPostMessage
// interfaces effectively
// [Solution]- Fix in string.c to handle cursor and line positions. The
// files Protocol.c, Protocol.h and AmiPostMgr.h have the new interface
// implementaion to get the attribute.
// [Files] - Protocol.c, Protocol.h, AmiPostMgr.h and string.c
// 
// 6     11/23/10 5:14p Blaines
// [TAG] - EIP 45374
// [Category]- Function Request
// [Synopsis]- Need method to configure Post Menu programmatically, Items
// requested 
// - Exit Keys
// - Font Colors
// - Background Colors.
// [Solution]
//  - Create hook to set window color, 
//  - Add AMI_POSTMENU_ATTRIB_EXIT_KEY  attribute to POSTMENU_TEMPLATE to
// configure exit keys.
// [Files] - stylecommon.c, style.h, listbox.c, minisetupext.c,
// AMIPostMgr.h
// 
// [TAG] - EIP 47962
//  [Category]- Defect
//  [Symptom]- Post Manager's DisplayMsgBox displays a corrupted screen
//  When the French or Japanese langues are selected and a call is made to
// DisplayMsgBox, the screen that is displayed is corrupted
// 
//  [Rootcause]  
//  The bounding box area of the message box is drawn, which may not span
// previous screen redraws. 
// Therefore, artifacts from previous screen displays may appear.
//  [Solution]- Clear the screen before drawing message box to clear
// artifacts from previous screen redraws.
// [Files] - TseAdvanced.c,  AMIPostMgr.h,
// 
// 5     11/16/10 9:00a Mallikarjunanv
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
// 4     4/16/10 5:11p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:03a Mallikarjunanv
// updated year in copyright message
// 
// 3     2/04/10 12:01p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards.
// 
// 2     6/24/09 11:55a Blaines
// Coding standard update
// 
// 1     6/09/09 9:53a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:47p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:41p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     2/05/09 5:19p Madhans
// PostMgrStatus interface added.
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
// Name:		AMIPostMgr.h
//
// Description:	AMI post manager protocol related code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMI_POSTMGR_H_
#define	_AMI_POSTMGR_H_

#define AMI_POST_MANAGER_PROTOCOL_GUID \
   { 0x8A91B1E1, 0x56C7, 0x4ADC, 0xAB, 0xEB, 0x1C, 0x2C, 0xA1, 0x72, 0x9E, 0xFF }

#ifndef EFI_PROTOCOL_DEFINITION
#define TSE_STRINGIZE(a) #a
#define EFI_PROTOCOL_DEFINITION(a) TSE_STRINGIZE(Protocol/a.h)
#endif

#include EFI_PROTOCOL_DEFINITION(GraphicsOutput)
#include EFI_PROTOCOL_DEFINITION(SimpleTextIn)

#define AMI_POSTMENU_ATTRIB_FOCUS	0
#define AMI_POSTMENU_ATTRIB_NON_FOCUS	1
#define AMI_POSTMENU_ATTRIB_HIDDEN	2
#define AMI_POSTMENU_ATTRIB_EXIT_KEY	3

#define TSE_WINDOW_TYPE_SETUP			0
#define TSE_WINDOW_TYPE_POSTMENU		1

#define TSE_FILTER_KEY_NULL	        0
#define TSE_FILTER_KEY_NUMERIC	    1
#define TSE_FILTER_KEY_ALPHA	    2
#define TSE_FILTER_KEY_ALPHANUMERIC	3
#define TSE_FILTER_KEY_CUSTOM   	4


typedef struct {
	EFI_INPUT_KEY 	Key;
	UINT32 		KeyShiftState;
} AMI_POST_MGR_KEY;

typedef struct _TEXT_INPUT_TEMPLATE
{
	UINT16			ItemToken;
	UINT8	        MaxSize;
    UINT8			FilterKey;
    BOOLEAN         Hidden;
	CHAR16			*Value; 
}
TEXT_INPUT_TEMPLATE;

typedef VOID (EFIAPI *POSTMENU_FUNCTION) (VOID *CallbackContext);

typedef struct _POSTMENU_TEMPLATE
{
	UINT16			ItemToken;
	AMI_POST_MGR_KEY	Key;
	POSTMENU_FUNCTION	Callback;
	VOID			*CallbackContext; 
	UINT8			Attribute;
}
POSTMENU_TEMPLATE;

typedef EFI_GRAPHICS_OUTPUT_BLT_PIXEL EFI_UGA_PIXEL;

typedef enum _CO_ORD_ATTRIBUTE {
CA_AttributeLeftTop,
CA_AttributeCenterTop,
CA_AttributeRightTop,
CA_AttributeRightCenter,
CA_AttributeRightBottom,
CA_AttributeCenterBottom,
CA_AttributeLeftBottom,
CA_AttributeLeftCenter,
CA_AttributeCenter,
CA_AttributeCustomised
}CO_ORD_ATTRIBUTE;

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_HANDSHAKE) (
	VOID
	);

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_MESSAGE) (
	CHAR16	*Message
	);

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_MESSAGE_EX) (
	CHAR16	*Message,
    UINTN   Attribute
	);

typedef 
BOOLEAN
(EFIAPI *DISPLAY_TEXT_KEY_VALIDATE) (
	UINT16 ItemIndex,
    UINT16 Unicode,
    CHAR16	*Value
);

//Post message ex attributes
#define PM_EX_DONT_ADVANCE_TO_NEXT_LINE     0x00000001

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_QUIETBOOT_MESSAGE) (
    CHAR16 *Message,
    INTN CoOrdX,
    INTN CoOrdY,
    CO_ORD_ATTRIBUTE Attribute,
    EFI_UGA_PIXEL Foreground,
    EFI_UGA_PIXEL Background
    );

//Message box types
#define MSGBOX_TYPE_NULL		0
#define MSGBOX_TYPE_OK			1
#define MSGBOX_TYPE_OKCANCEL	2
#define MSGBOX_TYPE_YESNO		3
#define MSGBOX_TYPE_CUSTOM		4
//Message box result buttons
#define MSGBOX_OK				0
#define MSGBOX_CANCEL			1
#define MSGBOX_YES				0	
#define MSGBOX_NO				1
typedef enum _MSGBOX_EX_CATAGORY {
MSGBOX_EX_CATAGORY_NORMAL,
MSGBOX_EX_CATAGORY_HELP,
MSGBOX_EX_CATAGORY_QUERY,
MSGBOX_EX_CATAGORY_SUCCESS,
MSGBOX_EX_CATAGORY_WARNING,
MSGBOX_EX_CATAGORY_ERROR,
MSGBOX_EX_CATAGORY_HALT,
MSGBOX_EX_CATAGORY_PROGRESS,
MSGBOX_EX_ATTRIB_CLEARSCREEN=0x1000,
} MSGBOX_EX_CATAGORY;

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_MSG_BOX) (
    IN CHAR16  *MsgBoxTitle,
    IN CHAR16  *Message,
    IN UINT8   MsgBoxType,
    OUT UINT8  *MsgBoxSel
	);

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_TEXT_BOX) (
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE DisplayTextKeyValidate
	);



typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_SWITCH_TO_POST_SCREEN) (VOID);

typedef 
EFI_STATUS 
(EFIAPI *AMI_POST_MANAGER_SET_CURSOR_POSITION) (
	UINTN X,
	UINTN Y
	);

typedef 
EFI_STATUS 
(EFIAPI *AMI_POST_MANAGER_GET_CURSOR_POSITION) (
	UINTN *pX,
	UINTN *pY
	);

typedef 
EFI_STATUS 
(EFIAPI *AMI_POST_MANAGER_INIT_PROGRESSBAR) (
	UINTN x,
	UINTN y,
	UINTN w,
	UINTN h,
	UINTN delta
	);


typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_SET_PROGRESSBAR_POSITION) (
	);

typedef 
EFI_STATUS 
(EFIAPI *AMI_POST_MANAGER_SET_ATTRIBUTE) (
	UINT8 Attrib
	);

typedef 
EFI_STATUS 
(EFIAPI *AMI_POST_MANAGER_GET_ATTRIBUTE) (
	UINT8 *Attrib
	);


typedef enum _TSE_POST_STATUS {
TSE_POST_STATUS_BEFORE_POST_SCREEN,		// TSE Loaded and yet goto post screen
TSE_POST_STATUS_IN_POST_SCREEN,			// In the post screen
TSE_POST_STATUS_IN_QUITE_BOOT_SCREEN,	// In the quite boot screen
TSE_POST_STATUS_IN_BOOT_TIME_OUT,		// Witing for Boot timeout
TSE_POST_STATUS_ENTERING_TSE,			// Entering TSE
TSE_POST_STATUS_IN_TSE,					// Inside TSE
TSE_POST_STATUS_IN_BBS_POPUP,			// Inside BBS Poupup
TSE_POST_STATUS_PROCEED_TO_BOOT			// Outside TSE and Booting or in Shell
}TSE_POST_STATUS;

typedef
TSE_POST_STATUS
(EFIAPI *AMI_POST_MANAGER_POST_STATUS) (
	);

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_INFO_BOX) (
    IN CHAR16  *InfoBoxTitle,
    IN CHAR16  *InfoString,
    IN UINTN   Timeout,
    OUT EFI_EVENT  *Event
	);

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_MSG_BOX_EX) (
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

// ProgressBoxState
#define AMI_PROGRESS_BOX_INIT		1
#define AMI_PROGRESS_BOX_UPDATE		2
#define AMI_PROGRESS_BOX_CLOSE		3

typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DRAW_PROGRESS_BOX) (
IN UINT8	ProgressBoxState, 
IN CHAR16	*Title,
IN CHAR16	*Message,
IN CHAR16	*Legend,
IN UINTN 	Percent,	// 0 - 100
IN OUT VOID	**Handle,	//Out HANDLE. Valid Handle for update and close
OUT AMI_POST_MGR_KEY	*OutKey	//Out Key
);



typedef
EFI_STATUS
(EFIAPI *AMI_POST_MANAGER_DISPLAY_MENU) (
    
    IN VOID	*HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN UINT16 	LegendToken,
    IN POSTMENU_TEMPLATE *MenuData,
    IN UINT16 	MenuCount,
    OUT UINT16 *pSelection
);


typedef struct _AMI_POST_MANAGER_PROTOCOL
{
    AMI_POST_MANAGER_HANDSHAKE                  Handshake;
    AMI_POST_MANAGER_DISPLAY_MESSAGE            DisplayPostMessage;
    AMI_POST_MANAGER_DISPLAY_MESSAGE_EX         DisplayPostMessageEx;
    AMI_POST_MANAGER_DISPLAY_QUIETBOOT_MESSAGE  DisplayQuietBootMessage;
    AMI_POST_MANAGER_DISPLAY_MSG_BOX            DisplayMsgBox;
    AMI_POST_MANAGER_SWITCH_TO_POST_SCREEN      SwitchToPostScreen;
	AMI_POST_MANAGER_SET_CURSOR_POSITION		SetCurPos;
	AMI_POST_MANAGER_GET_CURSOR_POSITION		GetCurPos;
	AMI_POST_MANAGER_INIT_PROGRESSBAR			InitProgressBar;
	AMI_POST_MANAGER_SET_PROGRESSBAR_POSITION	SetProgressBarPosition;
	AMI_POST_MANAGER_POST_STATUS				GetPostStatus;
	AMI_POST_MANAGER_DISPLAY_INFO_BOX			DisplayInfoBox;
    AMI_POST_MANAGER_SET_ATTRIBUTE		SetAttribute;
    AMI_POST_MANAGER_DISPLAY_MENU		DisplayPostMenu;
    AMI_POST_MANAGER_DISPLAY_MSG_BOX_EX		DisplayMsgBoxEx;
    AMI_POST_MANAGER_DRAW_PROGRESS_BOX		DisplayProgress;
    AMI_POST_MANAGER_GET_ATTRIBUTE		GetAttribute;	//EIP-41838: New interface to get the attribute value
    AMI_POST_MANAGER_DISPLAY_TEXT_BOX       DisplayTextBox;
}
AMI_POST_MANAGER_PROTOCOL;

extern EFI_GUID	gAmiPostManagerProtocolGuid;

//EIP 128665 starts
#define TSE_INVALIDATE_BGRT_STATUS_PROTOCOL_GUID \
   { 0x73905351, 0xeb4d, 0x4637, 0xa8, 0x3b, 0xd1, 0xbf, 0x6c, 0x1c, 0x48, 0xeb }

typedef EFI_STATUS (EFIAPI *INVALIDATE_BGRT_STATUS) (void);
typedef struct _TSE_INVALIDATE_BGRT_STATUS_PROTOCOL
{
	INVALIDATE_BGRT_STATUS 	InvalidateBgrtStatusByProtocol;
}TSE_INVALIDATE_BGRT_STATUS_PROTOCOL;

extern EFI_GUID	gTSEInvalidateBgrtStatusProtocolGuid;
///EIP 128665 ends

#endif /* _AMI_POSTMGR_H_ */

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
