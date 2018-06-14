//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/bootflow.h $
//
// $Author: Arunsb $
//
// $Revision: 15 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/bootflow.h $
// 
// 15    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 13    9/17/12 5:59a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 11    8/29/12 12:32p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 10    8/23/12 6:26p Arunsb
// Reverted back 2.15.1229 for making GTSE, TSELite and BootOnly labels
//
// 9     8/21/12 7:54p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 8     6/29/11 5:25a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
//                 Added BOOT_FLOW_HOTKEY_BOOT bootflow option for
// honoring the hot key boot.
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 7     6/20/11 3:45p Arunsb
// [TAG]           EIP57660 
// [Category]      New Feature
// [Description]   Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.
// [Files]         amitse.sdl, bootflow.c, bootflow.h, commonoem.c, boot.c
// and protocol.c
// 
// 6     6/10/11 2:39p Arunsb
// [TAG]        EIP57660
// [Category]   New Feature
// [Description]    Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.2
// [Files]          boot.c, bootflow.c and bootflow.h
// 
// 5     6/08/11 11:38p Arunsb
// [TAG]  		EIP57650
// [Category]  	New Feature
// [Description]  	Support in TSE Out of resources boot flow option.
// [Files]  		bootflow.c and bootflow.h
// 
// 4     9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 4     9/08/10 6:57a Mallikarjunanv
// EIP-42080: TSE updates with respect to Fast Boot Support
// 
// 3     4/13/10 5:12p Madhans
// EIP: 37439 To support extended OEM Key support.
// 
// 2     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:49p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
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
// Name:		bootflow.h
//
// Description:	bootflow header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _BOOTFLOW_H_
#define	_BOOTFLOW_H_

/* EF152FB4-7B2F-427D-BDB4-7E0A05826E64 */
#define	BOOT_FLOW_VARIABLE_GUID \
	{ 0xEF152FB4, 0x7B2F, 0x427D, 0xBD, 0xB4, 0x7E, 0x0A, 0x05, 0x82, 0x6E, 0x64 }

#define	TPM_BOOT_FLOW_VARIABLE_GUID \
	{ 0xb6460a49, 0x0ac1, 0x484f, 0xae, 0x58, 0xf1, 0x6e, 0xb2, 0x39, 0xdb, 0x3d }

#define	BOOT_FLOW_CONDITION_NORMAL	0
#define	BOOT_FLOW_CONDITION_ERROR	1
#define	BOOT_FLOW_CONDITION_RECOVERY 2
#define	BOOT_FLOW_CONDITION_FIRST_BOOT 4

#define	BOOT_FLOW_CONDITION_OEM_KEY1	0x00001001
#define	BOOT_FLOW_CONDITION_OEM_KEY2	0x00001002
#define	BOOT_FLOW_CONDITION_OEM_KEY3	0x00001003
#define	BOOT_FLOW_CONDITION_OEM_KEY4	0x00001004
#define	BOOT_FLOW_CONDITION_OEM_KEY_CALLBACK	0x00001005
#define BOOT_FLOW_CONDITION_NO_SETUP	        5
#define	BOOT_FLOW_CONDITION_BBS_POPUP	        6
#define	BOOT_FLOW_CONDITION_FAST_BOOT	        7
#define BOOT_FLOW_CONDITION_PCI_OUT_OF_RESOURCE 9
#define	BOOT_FLOW_HOTKEY_BOOT                   0xA
#define	BOOT_FLOW_CONDITION_OS_UPD_CAP 			0xB			//EIP93521
#define	BOOT_FLOW_CONDITION_NULL	0xFFFFFFFF

typedef struct _BOOT_FLOW	BOOT_FLOW;

typedef EFI_STATUS	(*BOOT_FLOW_CALLBACK)( BOOT_FLOW * );

struct _BOOT_FLOW
{
	UINT32				Condition;
	UINT16				PageClass;
	UINT16				PageSubClass;
	UINT16				PageFormID;
	UINT32				ControlNumber;
	UINT16				MessageBoxToken;
	UINT16				MessageBoxTimeout;
	BOOLEAN				GotoPageOnEntry;
	BOOLEAN				ProceedBooting;
	BOOLEAN				InfiniteLoop;
	BOOLEAN				LaunchShell;
	BOOLEAN				DoNotEnterSetup;
	BOOT_FLOW_CALLBACK	CallbackFunction;
};

EFI_STATUS BootFlowManageEntry( VOID );
EFI_STATUS BootFlowManageExit( VOID );
VOID _BootFlowShowMessageBox( BOOT_FLOW *bootFlowPtr );
VOID _BootFlowSetActivePage( BOOT_FLOW *bootFlowPtr );
VOID _BootFlowSetActiveControl( BOOT_FLOW *bootFlowPtr );

EFI_STATUS	OemKey1Hook ( BOOT_FLOW * );
EFI_STATUS	OemKey2Hook ( BOOT_FLOW * );
EFI_STATUS	OemKey3Hook ( BOOT_FLOW * );
EFI_STATUS	OemKey4Hook ( BOOT_FLOW * );
EFI_STATUS	DoPopup( BOOT_FLOW * );
//EFI_STATUS	DoPopupMenu( BOOT_FLOW * );
//EFI_STATUS	DoBootOnlyPopupMenu( BOOT_FLOW * );
EFI_STATUS	FBBootFlow (BOOT_FLOW *);
EFI_STATUS	LaunchHotKeyBootOption (BOOT_FLOW *);
EFI_STATUS  OsUpdateCapsuleWrap (BOOT_FLOW *BootFlow);

#endif /* _BOOTFLOW_H_ */

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
