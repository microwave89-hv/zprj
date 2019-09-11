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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/bootflow.c $
//
// $Author: Premkumara $
//
// $Revision: 21 $
//
// $Date: 8/28/14 4:27a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/bootflow.c $
// 
// 21    8/28/14 4:27a Premkumara
// EIP-135253 Updating file name proper in #include section
// 
// 20    12/04/13 2:43p Arunsb
// [TAG]	EIP125219
// [Category]	Improvement
// [Description]	Add event at end of BootFlowManageExit() after second
// boot path
// [Files]	bootflow.c, AMIVfr.h
// 
// 19    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 17    9/17/12 5:59a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 15    8/29/12 12:31p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 14    8/23/12 6:25p Arunsb
//
// 13    8/21/12 7:53p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 12    5/28/12 2:50a Arunsb
// [TAG]  		EIP88447
// [Category]  	New Feature
// [Description]  	Disable UEFI boot option in BIOS setup should not load
// the default image \EFI\BOOT\BOOT{machine type short-name}.EFI
// [Files]  		Amitse.sdl, commonhelper.c and bootflow.c
// 
// 11    6/29/11 5:37a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
//                 Added BOOT_FLOW_HOTKEY_BOOT bootflow option in
// BOOT_FLOW.
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 10    6/23/11 7:41p Arunsb
// [TAG]           EIP57660 
// [Category]      New Feature
// [Description]   Non-removable media boot behavior as described in UEFI
//                 specification v 2.3.1, p. 3.4.1.
//                 Checks for the setup key if no boot options avail
//                 or not succedded to boot. If setup key pressed launches
// the setup.
//                 If no boot option avail then inserting thumb drive with
// image efi\boot\bootxxxx.efi TSE will launch that image.     
// [Files]         amitse.sdl, bootflow.c and protocol.c
// 
// 9     6/20/11 3:43p Arunsb
// [TAG]           EIP57660 
// [Category]      New Feature
// [Description]   Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.
//                 If BOOT_FLOW's LaunchShell param sets to
// BOOTFLOW_EXIT_LAUNCH_DEFAULT_BOOTIMAGE then TSE tries to load the
//                 efi/boot/bootxxxx.efi from any of the file system.
//                 If BOOT_FLOW's InfiniteLoop param sets to
// BOOTFLOW_EXIT_INFINITE_LOOP_LAUNCH_SETUP then TSE tried to enter the
// setup
//                 if no boot option present or succeeded to boot. Enters
// to setup only when setup key detected after boot options failure
// occurs.
// [Files]         amitse.sdl, bootflow.c, bootflow.h, commonoem.c, boot.c
// and protocol.c
// 
// 8     6/10/11 2:38p Arunsb
// [TAG]        EIP57660
// [Category]   New Feature
// [Description]    Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.2
// [Files]          boot.c, bootflow.c and bootflow.h
// 
// 7     6/08/11 11:38p Arunsb
// [TAG]  		EIP57650
// [Category]  	New Feature
// [Description]  	Support in TSE Out of resources boot flow option.
// [Files]  		bootflow.c and bootflow.h
// 
// 6     3/15/11 2:39a Pugazhendhip
// [TAG]  		EIP54858
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When developing projects with a custom Bootflow and custom
// Setup, this PageFormID may not exist and will therefore cause a build
// error
// [RootCause]  	The MAIN_MAIN and MAIN_FORM_SET_CLASS are defined inside
// the ifdef condition. Hence, when the condition macro is defined in the
// project, the MAIN_MAIN and MAIN_FORM_SET_CLASS  macros are not
// available which causes the build error in the _gBootFlowTable array
// declaration.
// [Solution]  	Moved the following code fragment  outside of else
// condition compiler case (TSE_FOR_APTIO_4_50)
// 
// #ifndef MAIN_FORM_SET_CLASS
// #define MAIN_FORM_SET_CLASS 1
// #endif
// 
// #ifndef MAIN_MAIN
// #define MAIN_MAIN 1
// #endif
// 
// [Files]  		bootflow.c
// 
// 5     9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 6     9/08/10 6:57a Mallikarjunanv
// EIP-42080: TSE updates with respect to Fast Boot Support
// 
// 5     4/13/10 5:12p Madhans
// EIP: 37439 To support extended OEM Key support.
// 
// 4     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 3     1/29/10 5:17p Madhans
// changes to support UEFI 2.1 build also.
// 
// 2     1/09/10 2:24a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 2     5/07/09 10:31a Madhans
// Changes After Bin module.
// 
// 3     5/05/09 3:10p Madhans
// gBootFlowTable points to the Bootflow. OEM may update this Pointer with
// OEM bootflow table.
// 
// 2     5/01/09 8:25p Mallikarjunanv
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		bootflow.c
//
// Description:	This file bootflow related functions and tables
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifdef TSE_FOR_APTIO_4_50

#include "Token.h"
#include <Efi.h>
#include <Protocol/SimpleTextIn.h>

#include "setup.h" // for MAIN_FORM_SET_CLASS
#include "AutoId.h" // for MAIN_MAIN

#else //#ifdef TSE_FOR_APTIO_4_50

#include "minisetup.h"

#endif //#ifdef TSE_FOR_APTIO_4_50

#include "AmiVfr.h"
#include "Variable.h"
#include "boot.h"
#include "bootflow.h"
#include "mem.h"
#include "commonoem.h"
#include "HookAnchor.h"

//ray_override / Fixed System Reboot by WDT if There's no Boot Devices / Added >>
#include <AmiDxeLib.h>
//ray_override / Fixed System Reboot by WDT if There's no Boot Devices / Added <<

#ifndef MAIN_FORM_SET_CLASS
#define MAIN_FORM_SET_CLASS 1
#endif

#ifndef MAIN_MAIN
#define MAIN_MAIN	1
#endif

extern BOOLEAN gEnterSetup;
extern EFI_GUID gEfiShellFileGuid;

EFI_GUID _gBootFlowGuid = BOOT_FLOW_VARIABLE_GUID;
static EFI_GUID _gTPMBootFlowGuid = TPM_BOOT_FLOW_VARIABLE_GUID;

VOID SetupDebugPrint(IN CONST CHAR8  *Format, ...) ;
#if SUPPRESS_PRINT
    #define SETUP_DEBUG_TSE(format,...)
#else //Else of SUPPRESS_PRINT
    #define SETUP_DEBUG_TSE(format,...) SetupDebugPrint(format, __VA_ARGS__)
#endif

static BOOT_FLOW _gBootFlowTable[] =
{
//	{ Condition,						            PageClass,				PageSubClass,	PageFormID,	ControlNumber,	MessageBoxToken,	MessageBoxTimeout,	GotoPageOnEntry,	ProceedBooting,	InfiniteLoop,	                            LaunchShell,	DoNotEnterSetup,	CallbackFunction },
    { BOOT_FLOW_CONDITION_NORMAL,		            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,	        BOOT_FLOW_NORMAL_INFINITE_LOOP,	            BOOT_FLOW_NORMAL_LAUNCH_DEFAULT_BOOTIMAGE,  FALSE,				NULL },
	{ BOOT_FLOW_CONDITION_ERROR,		            ERROR_MANAGER_KEY_ID,	0,				1,			0,				0,					0,					TRUE,				FALSE,			FALSE,			                            TRUE,			                            FALSE,				NULL },
	{ BOOT_FLOW_CONDITION_RECOVERY,		            0x40,					0,				1,			0,				0,					0,					TRUE,				TRUE,			FALSE,			                            TRUE,			                            FALSE,				NULL },
	{ BOOT_FLOW_CONDITION_PCI_OUT_OF_RESOURCE,		0x79,		            0,				1,			0,				0,					0,					TRUE,				TRUE,			FALSE,			                            TRUE,			                            FALSE,				NULL },
	{ BOOT_FLOW_CONDITION_FIRST_BOOT,	            MAIN_FORM_SET_CLASS,	0,				MAIN_MAIN,	0,				0,					0,					TRUE,				TRUE,			FALSE,			                            TRUE,			                            FALSE,				NULL },
	{ BOOT_FLOW_CONDITION_OS_UPD_CAP,	            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&OsUpdateCapsuleWrap },		//EIP93521
    { BOOT_FLOW_HOTKEY_BOOT,                        0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&LaunchHotKeyBootOption },
#if SETUP_OEM_KEY1_ENABLE
	{ BOOT_FLOW_CONDITION_OEM_KEY1,		            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&OemKey1HookHook },
#endif
#if SETUP_OEM_KEY2_ENABLE
	{ BOOT_FLOW_CONDITION_OEM_KEY2,		            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&OemKey2HookHook },
#endif
#if SETUP_OEM_KEY3_ENABLE
	{ BOOT_FLOW_CONDITION_OEM_KEY3,		            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&OemKey3HookHook },
#endif
#if SETUP_OEM_KEY4_ENABLE
	{ BOOT_FLOW_CONDITION_OEM_KEY4,		            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&OemKey4HookHook },
#endif
#if SETUP_BBS_POPUP_ENABLE
	{ BOOT_FLOW_CONDITION_BBS_POPUP,	            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				&DoPopup },
#endif
	{ BOOT_FLOW_CONDITION_OEM_KEY_CALLBACK,	        0,					    0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            FALSE,			                            FALSE,				NULL }, // Callback is null and on OEMkey press it will updated.
	{ BOOT_FLOW_CONDITION_NO_SETUP,		            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			TRUE,			                            FALSE,			                            TRUE,				NULL },
#if FAST_BOOT_SUPPORT
	{ BOOT_FLOW_CONDITION_FAST_BOOT,	            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            TRUE,			                            TRUE,				&FBBootFlow },
#endif
	// this MUST be the last entry in the boot flow table
	{ BOOT_FLOW_CONDITION_NULL,			            0,						0,				0,			0,				0,					0,					FALSE,				TRUE,			FALSE,			                            TRUE,			                            FALSE,				NULL }
};

// Set the initial Bootflow table.
// OEM may have thier own Bottflow table and update the gBootFlowTable with that in the Entry hooks.
BOOT_FLOW	*gBootFlowTable = _gBootFlowTable;
EFI_STATUS LaunchSecondaryBootPath (CHAR16 *);			//EIP 88447
EFI_STATUS EfiLibNamedEventSignal (IN EFI_GUID  *Name );      //EIP125219

//ray_override / Fixed System Reboot by WDT if There's no Boot Devices / Added >>
VOID bootflow_F81866ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F81866_CONFIG_INDEX, Index);
	IoWrite8(F81866_CONFIG_DATA, Data);
}
UINT8 bootflow_F81866ConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(F81866_CONFIG_INDEX, Index);
	Data8 = IoRead8(F81866_CONFIG_DATA);
	return Data8;
}
VOID bootflow_F81866LDNSelect(UINT8 Ldn)
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
	IoWrite8(F81866_CONFIG_DATA, Ldn);
}
VOID bootflow_F81866EnterConfigMode()
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
}
VOID bootflow_F81866ExitConfigMode()
{
	// Exit config mode
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);
}

VOID bootflow_F81866WDTDisable()
{
	bootflow_F81866EnterConfigMode() ;
	bootflow_F81866LDNSelect(F81866_LDN_WDT) ;
	// WDT Disabled
	bootflow_F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) & ~BIT5 ) ;
	bootflow_F81866ExitConfigMode() ;
}
//ray_override / Fixed System Reboot by WDT if There's no Boot Devices / Added <<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootFlowManageEntry
//
// Description:	Determines boot flow entry path based on the boot
//              flow variable.
//
// Input:		VOID
//
// Output:		EFI_SUCCESS: Normal boot
//              EFI_UNSUPPORTED: do not proceed to boot
//              EFI_NOT_STARTED: Do not enter setup
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootFlowManageEntry( VOID )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32 condition = BOOT_FLOW_CONDITION_NORMAL;
	UINT32 *conditionPtr;
	UINTN size = 0;

	BOOT_FLOW *bootFlowPtr;

	SETUP_DEBUG_TSE ("\n[TSE] Entering BootFlowManageEntry");
	conditionPtr = VarGetNvramName( L"BootFlow", &_gBootFlowGuid, NULL, &size );
	if ( conditionPtr != NULL )
		condition = *conditionPtr;

	MemFreePointer( (VOID **)&conditionPtr );

	size = 0;
    conditionPtr = VarGetNvramName( L"TPMBootFlow", &_gTPMBootFlowGuid, NULL, &size );

    if ( conditionPtr != NULL )
    {
        if(*conditionPtr != BOOT_FLOW_CONDITION_NORMAL)
            condition = *conditionPtr;
    }

	MemFreePointer( (VOID **)&conditionPtr );
	bootFlowPtr = gBootFlowTable;
	for ( bootFlowPtr = gBootFlowTable;
			bootFlowPtr->Condition != BOOT_FLOW_CONDITION_NULL; bootFlowPtr++ )
	{
		if ( condition != bootFlowPtr->Condition )
			continue;
		SETUP_DEBUG_TSE ("\n[TSE] BootFlow condition is %d", condition);
		if ( bootFlowPtr->CallbackFunction != NULL )
			Status = bootFlowPtr->CallbackFunction( bootFlowPtr );
		if ( ! bootFlowPtr->ProceedBooting )
			Status = EFI_UNSUPPORTED;

		if ( bootFlowPtr->MessageBoxToken != 0 )
			_BootFlowShowMessageBox( bootFlowPtr );
		if ( ( bootFlowPtr->GotoPageOnEntry ) && ( bootFlowPtr->PageClass != 0 ) )
		{
			_BootFlowSetActivePage( bootFlowPtr );
			_BootFlowSetActiveControl( bootFlowPtr );
		}

		if(bootFlowPtr->DoNotEnterSetup)
		{
			gEnterSetup = FALSE;
			Status = EFI_NOT_STARTED;
		}

		break;
	}
	SETUP_DEBUG_TSE ("\n[TSE] Exiting BootFlowManageEntry");
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootFlowManageExit
//
// Description:	Determines boot flow exit path based on the boot
//              flow variable.
//
// Input:		VOID
//
// Output:		EFI_UNSUPPORTED: enter setup if all the boot options
//              fail
//              EFI_NOT_STARTED: try again and again if all boot
//              options fail
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootFlowManageExit (VOID)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32 condition = BOOT_FLOW_CONDITION_NORMAL;
	UINT32 *conditionPtr;
	UINTN size = 0;
	BOOT_FLOW *bootFlowPtr;
	EFI_GUID	AfterLastBootGuid = AMITSE_AFTER_LAST_BOOT_OPTION_GUID;
	
	SETUP_DEBUG_TSE ("\n[TSE] Entering BootFlowManageExit");
	conditionPtr = VarGetNvramName( L"BootFlow", &_gBootFlowGuid, NULL, &size );
	if ( conditionPtr != NULL )
		condition = *conditionPtr;

	MemFreePointer( (VOID **)&conditionPtr );

	size =0;
    conditionPtr = VarGetNvramName( L"TPMBootFlow", &_gTPMBootFlowGuid, NULL, &size );

	if ( conditionPtr != NULL )
	{
		if(*conditionPtr != BOOT_FLOW_CONDITION_NORMAL)
		condition = *conditionPtr;
	}

	MemFreePointer( (VOID **)&conditionPtr );

//ray_override / Fixed System Reboot by WDT if There's no Boot Devices / Added >>
	bootflow_F81866WDTDisable();
//ray_override / Fixed System Reboot by WDT if There's no Boot Devices / Added <<
	bootFlowPtr = gBootFlowTable;
	for ( bootFlowPtr = gBootFlowTable;
			bootFlowPtr->Condition != BOOT_FLOW_CONDITION_NULL; bootFlowPtr++ )
	{
		if ( condition != bootFlowPtr->Condition )
			continue;
		SETUP_DEBUG_TSE ("\n[TSE] BootFlow condition is %d", condition);

		if ( bootFlowPtr->PageClass != 0 )
		{
			_BootFlowSetActivePage( bootFlowPtr );
			_BootFlowSetActiveControl( bootFlowPtr );
			Status = EFI_NOT_STARTED;
			break;
		}

		if ( ! bootFlowPtr->InfiniteLoop )
			Status = EFI_UNSUPPORTED;
		else
			Status = EFI_NOT_STARTED;

		if (bootFlowPtr->LaunchShell)                 
		{
			LaunchSecondaryBootPath (gBootFileName);			//EIP 88447
			EfiLibNamedEventSignal (&AfterLastBootGuid);		//EIP125219 notifying last boot
			BootLaunchGuid (&gEfiShellFileGuid);
		}
		break;
	}
	SETUP_DEBUG_TSE ("\n[TSE] Exiting BootFlowManageExit");
	return Status;
}

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
