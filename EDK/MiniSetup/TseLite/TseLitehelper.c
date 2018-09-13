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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/TseLitehelper.c $
//
// $Author: Premkumara $
//
// $Revision: 18 $
//
// $Date: 7/02/13 10:09a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/TseLitehelper.c $
// 
// 18    7/02/13 10:09a Premkumara
// [TAG]  		EIP120011
// [Category]  	Improvement
// [Description]  	Variable BootOrder and LegacyDevOrder need
// fool-proofing function when TSE load variabled
// [Files]  		Bbs.c, Boot.c, Callback.c, TseLiteHelper.c, Variable.c
// 
// 17    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 22    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 16    2/03/12 8:43a Arunsb
// While booting to shell it appears on different colors other than black
// so setting the background attribute with black color.
// 
// 15    12/07/11 11:26p Arunsb
// [TAG]  		EIP77493
// [Category]  	New Feature
// [Description]  	Provide the alternative way for _ActionReadKey
// [Files]  		AMITSE.sdl and TseLitehelper.c
// 
// 14    11/30/11 1:32p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 13    11/13/11 1:07p Arunsb
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
// 12    9/29/11 7:02p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 11    2/04/11 4:38p Mallikarjunanv
// Added dummy function for UpdateBootVariables() 
// 
// 10    2/01/11 7:35p Madhans
// [TAG] - EIP 50737 
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom] - Suppressing the Interactive control does not work
// correctly.
// [RootCause] - The control conditional pointer if not set correctly.
// [Solution]- To fix the Control condition pointer. And identify the
// suppress if related to UEFI action control
// [Files] - UefiAction.c TseLiteHelper.c hii.h uefi20wapper.c
// uefi21wapper.c
// 
// 9     10/05/10 12:20p Mallikarjunanv
// added ShowPostProgress function for TSE Lite
// 
// 8     9/20/10 6:47p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 7     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 15    9/16/10 3:13p Madhans
// To Avoid build issues with TSE_USE_EDK_LIBRARY Building.
// 
// 14    8/27/10 5:05a Mallikarjunanv
// EIP-39334: support to build TSE without the CSM module support
// 
// 13    6/14/10 7:10p Madhans
// Nt32 build support.
// 
// 12    3/23/10 5:24p Blaines
// Add support for PostManager Extentions
// 
// 11    2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 10    1/29/10 4:38p Madhans
// To iniltize it properly
// 
// 9     1/09/10 7:05a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 8     9/15/09 9:50a Sudhirv
// updated the handling of Add Del Boot option
// 
// 7     8/19/09 6:33p Madhans
// IsToggleStateKey Function added to findout invalid action keys
// correctly.
// 
// 6     8/13/09 7:40a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 5     7/20/09 1:22p Mallikarjunanv
// updated the code with token PASSWORD_WITH_SPECIAL_CHAR_SUPPORT
// 
// 4     6/23/09 6:53p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 3     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 2     6/08/09 5:36p Madhans
// Fix for SetupHang issue in TSE Lite.
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:07p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:13p Madhans
// Add/del boot option and other fixes.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
// 
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TSELiteHelper.c
//
// Description:	This file contains code specific to TSE Lite flavor
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

extern BOOLEAN gQuietBoot;

UINT32 GetControlConditionVarId(CONTROL_INFO *control);
BOOLEAN CheckIsAllowedPasswordChar(CHAR16 Char);
extern APPLICATION_DATA	*gApp;

// TSELiteMinisetup
#define	SETUP_VARIABLE_GUID	\
	{ 0xEC87D643, 0xEBA4, 0x4BB5, { 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 } }


static SETUP_PKG _SetupPackageTemplate = { 
		{'$', 'S', 'P', 'F'}, //PackageSignature[4];
		0x0102, 			//StructureRevision;
		0x100,				//PackageVersion;
		{0,0,0,0,0,0},		//Reserved[6];
		SETUP_VARIABLE_GUID, //PackageGuid;
		0, 					//PackageVariable;
		0, 					//PackageScreen;
		0, 					//PackagePageList;
		0, 					//PackageControlOffset;
		0, 					//PackageVariableList;
		0, 					//PackageHpkData;
		0, 					//PackageGuidList;
		0, 					//PackagePageIdList;
		0 					//PackageIfrData;			
};

static SCREEN_INFO _SetupPackageScreen = {
	{0},					//MainHandle;		
	STR_MAIN_TITLE,		//MainTitle;		
	STR_MAIN_COPYRIGHT, //MainCopyright;
	STR_EVAL_MSG,		//MainHelpTitle;	
	0,					//MainMenuCount;	
	0					//MainNavCount;
};


static PAGE_INFO _SetupPageInfo = 
{
		{0},			//		PageHandle;
		0,			//		PageIdIndex;
		0,			//		PageFormID;
		0,			//		PageTitle;
		0,			//		PageSubTitle;
		0,			//		PageID;
		0,			//		PageParentID;
		{0},			//		PAGE_FLAGS		PageFlags;
		0,			//		PageVariable;
		{0},		//		PageControls;
};

static CONTROL_INFO _SetupControlInfo_N_N = {
		{0},			//	EFI_HII_HANDLE	ControlHandle;
		0,			//	UINT32			ControlVariable;
		{0},			//	UINT32			ControlConditionalVariable[2];
		0,			//	UINT16			ControlType;
		0,			//	UINT16			ControlPageID;
		0xFFFF,			//	UINT16			ControlDestPageID;
		{0},		//	CONTROL_FLAGS	ControlFlags;
		0,			//	UINT16			ControlHelp;
		0,			//	UINT16			ControlLabel;
		0,			//	UINT16			ControlIndex;
		0,			//	UINT16			ControlLabelCount;
		{0},			//	union {
					//	UINTN			ControlPtr;
					//	UINT64	res1;
					//	};
		{0},			//	union {
					//	INTN			ControlConditionalPtr;
					//	UINT64	res2;
					//	};A
		0,			//	UINT16			ControlDataLength;
		0,			//	UINT16			ControlDataWidth;
		0			//	UINT16			QuestionId;
};

#define _VARIABLE_COUNT		17 
#define _GUID_COUNT			5

static VARIABLE_INFO _SetupVariableInfo[_VARIABLE_COUNT] = { 	
	{SETUP_VARIABLE_GUID , 		L"Setup",			0x07,0},
	{EFI_GLOBAL_VARIABLE_GUID , L"Dummy",			0x17,0},
	{EFI_GLOBAL_VARIABLE_GUID , L"Timeout",			0x07,0},
	{USER_DEFAULTS_GUID , 		L"UserDefaults",	0x07,0},
	{ERROR_MANAGER_GUID , 		L"ErrorManager",	0x07,0},
	{AMITSESETUP_GUID , 		L"AMITSESetup",		0x07,0},
	{IDE_SECURITY_CONFIG_GUID , L"IDESecDev",		0x07,0},
	{EFI_GLOBAL_VARIABLE_GUID , L"BootOrder",		0x17,0},
	{LEGACY_DEV_ORDER_GUID , 	L"LegacyDevOrder",	0x17,0},
	{DEL_BOOT_OPTION_GUID , 	L"DelBootOption",	0x17,0},
	{ADD_BOOT_OPTION_GUID , 	L"AddBootOption",	0x17,0},
	{BOOT_MANAGER_GUID , 		L"BootManager",		0x07,0},
	{BOOT_NOW_COUNT_GUID , 		L"BootNowCount",	0x07,0},
	{LEGACY_DEV_ORDER_GUID , 	L"LegacyDev",		0x01,0},
	{AMI_CALLBACK_GUID , 		L"AMICallback",		0x01,0},
	{LEGACY_DEV_ORDER_GUID , 	L"LegacyGroup",		0x01,0},
	{BOOT_NOW_COUNT_GUID , 		L"SetupSaveState",	0x02,0},
};

static GUID_INFO _SetupGUIDInfo[_GUID_COUNT] = {
	// Needs to be first on List for patching up later.
	{EFI_GLOBAL_VARIABLE_GUID ,	L"Dummy",		{1},5}, // For lang codes/platformlangcode
	{BOOT_MANAGER_GUID , 		L"BootManager",		{1},1},
	{BOOT_NOW_COUNT_GUID , 		L"BootNowCount",	{1},1},
	{AMI_CALLBACK_GUID , 		L"AMICallback",		{1},2},
	{ADD_BOOT_OPTION_GUID ,		L"AddBootOption",	{0},9}
};

#pragma pack(8)
typedef struct _TSE_SETUP_PACKAGE
{
	SETUP_PKG 		SetupPkg;
	SCREEN_INFO 	ScreenInfo;
	PAGE_LIST		PageList;
	UINT32			PageOffset[1]; // Increase if you have more pages - Dummy
	PAGE_INFO		PageInfo[1];   // Increase if you have more pages - Dummy

	CONTROL_INFO	ControlInfo[1];// Increase if controls	- Dummy

	VARIABLE_LIST	VariableList;
	UINT32			VariableOffset[_VARIABLE_COUNT]; // Increase if you have more Variable
	VARIABLE_INFO	VariableInfo[_VARIABLE_COUNT];
	HPK_INFO		HpkInfo[1]; //- Dummy	
	GUID_LIST		GuidList;
	UINT32			GuidOffset[_GUID_COUNT]; // Increase if you have more GUID
	GUID_INFO		GuidInfo[_GUID_COUNT];
	PAGE_ID_LIST	PageIdList;
	UINT32			PageIdOffset[1]; // Increase if you have more Page - Dummy
	PAGE_ID_INFO	PageIdInfo[1];	// Increase if you have more Page - Dummy
}TSE_SETUP_PACKAGE;

#pragma pack()

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitApplicationData
//
// Description:	Initlizes the TSE Lite Setupdata.
//
// Input:		ImageHandle
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	InitApplicationData(EFI_HANDLE ImageHandle)
{
	EFI_STATUS	Status=EFI_SUCCESS;
//	UINTN FillSize = 0;
	UINTN i;
	CHAR16 *name = NULL;

	//TODO
	// Init the Application data
	// Hardcoded Application data for the TSE Lite
	gApplicationData = EfiLibAllocateZeroPool( 0x1000 ); // Allocate more of you add more 

	// SETUP_PKG
	MemCopy(gApplicationData,&_SetupPackageTemplate, sizeof(_SetupPackageTemplate) );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageVariable = 0;
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageScreen = STRUCT_OFFSET( TSE_SETUP_PACKAGE, ScreenInfo );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackagePageList = STRUCT_OFFSET( TSE_SETUP_PACKAGE, PageList );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageControlOffset = STRUCT_OFFSET( TSE_SETUP_PACKAGE, ControlInfo );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageVariableList = STRUCT_OFFSET( TSE_SETUP_PACKAGE, VariableList );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageHpkData = STRUCT_OFFSET( TSE_SETUP_PACKAGE, HpkInfo );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageGuidList = STRUCT_OFFSET( TSE_SETUP_PACKAGE, GuidList );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackagePageIdList = STRUCT_OFFSET( TSE_SETUP_PACKAGE, PageIdList );
	((TSE_SETUP_PACKAGE *)gApplicationData)->SetupPkg.PackageIfrData = sizeof(TSE_SETUP_PACKAGE);

	//SCREEN_INFO
	MemCopy(&((TSE_SETUP_PACKAGE *)gApplicationData)->ScreenInfo,&_SetupPackageScreen,sizeof(SCREEN_INFO));

	//PAGE_INFO
	MemSet(&_SetupPageInfo,sizeof(_SetupPageInfo),0);
	MemCopy(&((TSE_SETUP_PACKAGE *)gApplicationData)->PageInfo,&_SetupPageInfo,sizeof(_SetupPageInfo));

	//PAGE_LIST
	((TSE_SETUP_PACKAGE *)gApplicationData)->PageList.PageCount = 1;
	((TSE_SETUP_PACKAGE *)gApplicationData)->PageList.PageList[0] = (UINT32)((UINTN)(&((TSE_SETUP_PACKAGE *)gApplicationData)->PageInfo[0])-(UINTN)(gApplicationData));

	//CONTROL_INFO
	MemCopy(&((TSE_SETUP_PACKAGE *)gApplicationData)->ControlInfo,&_SetupControlInfo_N_N,sizeof(CONTROL_INFO));

	//VARIABLE_INFO
	name = GetVariableNameByID(VARIABLE_ID_LANGUAGE);
	EfiStrCpy(_SetupVariableInfo[VARIABLE_ID_LANGUAGE].VariableName, name);
	MemFreePointer(&name);
	MemCopy(&((TSE_SETUP_PACKAGE *)gApplicationData)->VariableInfo,&_SetupVariableInfo,sizeof(_SetupVariableInfo));

	//VARIABLE_LIST
	((TSE_SETUP_PACKAGE *)gApplicationData)->VariableList.VariableCount = _VARIABLE_COUNT;
	for(i=0;i<_VARIABLE_COUNT;i++)
		((TSE_SETUP_PACKAGE *)gApplicationData)->VariableList.VariableList[i] = (UINT32)((UINTN)(&((TSE_SETUP_PACKAGE *)gApplicationData)->VariableInfo[i])-(UINTN)(&((TSE_SETUP_PACKAGE *)gApplicationData)->VariableList));
	
	//GUID_INFO
	name = GetGUIDNameByID(VARIABLE_ID_LANGUAGE);
	EfiStrCpy(_SetupGUIDInfo[0].GuidName , name);
	MemFreePointer(&name);
	MemCopy(&((TSE_SETUP_PACKAGE *)gApplicationData)->GuidInfo,_SetupGUIDInfo,sizeof(_SetupGUIDInfo));

	//GUID_LIST
	((TSE_SETUP_PACKAGE *)gApplicationData)->GuidList.GuidCount = _GUID_COUNT;
	for(i=0;i<_GUID_COUNT;i++)
		((TSE_SETUP_PACKAGE *)gApplicationData)->GuidList.GuidList[i] = (UINT32)((UINTN)(&((TSE_SETUP_PACKAGE *)gApplicationData)->GuidInfo[i])-(UINTN)(&((TSE_SETUP_PACKAGE *)gApplicationData)->GuidList));

	return Status;
}

VOID TSELiteFixBootOrder(CONTROL_DATA *ControlData);
VOID TSELiteFixBBSOrder(CONTROL_DATA *ControlData);
VOID TSELiteFixBootOrderRide(CONTROL_DATA *ControlData);
VOID TSELiteFixAddBootOptionFileList(CONTROL_DATA *ControlData);
VOID TSELiteFixDelBootOptionFileList(CONTROL_DATA *ControlData);
#ifdef TSE_FOR_APTIO_4_50
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialUpdatePageControls
//
// Description:	Fix the Boot Order, BBS Order and Boot Override controls.
//
// Input:		CurrentPage
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialUpdatePageControls(UINT32 CurrentPage)
{
	UINT16 j=0;
	UINT32 CtrlCondVariable=0xFFFF, CtrlVariable=0xFFFF;
    CONTROL_INFO *control;

	CONTROL_DATA **ControlData;
    FRAME_DATA *fdata;

	fdata = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[StyleFrameIndexOf(MAIN_FRAME)]; 
	ControlData = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[StyleFrameIndexOf(MAIN_FRAME)]->ControlList;

	for(j=0;j < fdata->ControlCount;j++,ControlData++)
	{
		control = &(*ControlData)->ControlData;

		if( CheckControlCondition( control ) != COND_NONE)
			continue;

		CtrlCondVariable = GetControlConditionVarId(control);
		CtrlVariable = _GetControlVariable(control);

		switch( CtrlCondVariable)
		{	
		case VARIABLE_ID_BOOT_MANAGER:
			// For Boot Order Case
			if(( CtrlVariable == VARIABLE_ID_BOOT_ORDER) && 
			((control->ControlType == CONTROL_TYPE_ORDERED_LIST)||(control->ControlType == CONTROL_TYPE_POPUPSEL)))
				TSELiteFixBootOrder(*ControlData);

			// For Boot Override Case
			if( (control->ControlType == CONTROL_TYPE_SUBMENU) && 
				(control->ControlPageID == control->ControlDestPageID) )
				{
					((SUBMENU_DATA*)(*ControlData))->SubMenuType = 2;
					TSELiteFixBootOrderRide(*ControlData);
				}
				if(( CtrlVariable == VARIABLE_ID_DEL_BOOT_OPTION) && (control->ControlType == CONTROL_TYPE_POPUPSEL))
					TSELiteFixDelBootOptionFileList(*ControlData);
			break;
		case VARIABLE_ID_LEGACY_DEV_INFO:
			if(( CtrlVariable == VARIABLE_ID_BBS_ORDER) && 
			((control->ControlType == CONTROL_TYPE_ORDERED_LIST)||(control->ControlType == CONTROL_TYPE_POPUPSEL)))
				TSELiteFixBBSOrder(*ControlData);
			break;
		case VARIABLE_ID_AMI_CALLBACK:
			if( (control->ControlType == CONTROL_TYPE_SUBMENU) && 
				(control->ControlPageID == control->ControlDestPageID) )
				((SUBMENU_DATA*)(*ControlData))->SubMenuType = 2;
			break;
		case VARIABLE_ID_ADD_BOOT_OPTION:
			if( (control->ControlType == CONTROL_TYPE_POPUPSEL) )
				TSELiteFixAddBootOptionFileList(*ControlData);
			break;
		default:
			break;
		}
	}
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSELiteFixBootOrder
//
// Description:	Fixes the Boot Order OrderList.
//
// Input:		ControlData
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSELiteFixBootOrder(CONTROL_DATA *ControlData)
{
	POPUPSEL_DATA *popupSel = (POPUPSEL_DATA *)ControlData;
	UINT16 i=0;
	CHAR16 *BootStr;
    UINT16 *BootOrder=NULL;
    UINTN size = 0;

	BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );

	if (NULL != BootOrder)//EIP-75352 Suppress the warnings from static code analyzer
	{
		for(i=0;i<popupSel->ItemCount;i++)
		{
			BootStr = BootGetBootNowName(i,0,1);
			popupSel->PtrTokens[i].Option = HiiAddString( popupSel->ControlData.ControlHandle, BootStr );
			popupSel->PtrTokens[i].Value = BootOrder[i];
		}
    	MemFreePointer((VOID **) &BootOrder);
	}
}

// Fixes the BBS Order Name and Value
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSELiteFixBBSOrder
//
// Description:	Fixes the BBS Order Orderlist.
//
// Input:		ControlData
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSELiteFixBBSOrder(CONTROL_DATA *ControlData)
{
	POPUPSEL_DATA *popupSel = (POPUPSEL_DATA *)ControlData;
    CONTROL_INFO *control;
	PAGE_INFO * pageInfo;
	UINT16 DevType;
	BBS_ORDER_TABLE *devOrder=NULL,*TempDevOrder=NULL;
	UINTN size = 0,i,j;
    BOOT_DATA * bootData=NULL;
    UINT16 *BootOrder=NULL;
	UINT16 Count;


	control = &(ControlData)->ControlData;
	pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[control->ControlPageID]);
	
	// to find the Devicetype based on the FORM ID
	switch(pageInfo->PageFormID)
	{
	case HARD_DISK_ORDER_FORM:
		DevType = BBS_TYPE_HARDDRIVE;break;
	case CDROM_ORDER_FORM:
		DevType = BBS_TYPE_CDROM;
		break;
	case FLOPPY_DISK_ORDER_FORM:
		DevType = BBS_TYPE_FLOPPY;
		break;
	case NETWORK_ORDER_FORM:
		DevType = BBS_TYPE_EMBEDDED_NETWORK;
		break;
	case BEV_ORDER_FORM:
		DevType = BBS_TYPE_BEV;
		break;
	default:
		return;
	}

	devOrder =	VarGetVariable( VARIABLE_ID_BBS_ORDER, &size );
	//EIP-75352 Suppress the warnings from static code analyzer
	if (NULL == devOrder)
		return;

	for(i=0;i<size;)
	{
		TempDevOrder = (BBS_ORDER_TABLE *)(((UINT8*)devOrder)+i);

		if ( (TempDevOrder->Length >= size) || (0 == TempDevOrder->Length) ) //EIP-120011
		{
			return;
		}

		if(TempDevOrder->Type == DevType)
			break;
		i = i+ sizeof(UINT32)+ TempDevOrder->Length;
	}
	if(i<size) // If Device type found in LegacydevOrder.
	{
		Count = (TempDevOrder->Length/sizeof(UINT16))-1;
		if(Count==popupSel->ItemCount)
		{
			// Find the BOOT data of DevType
			BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
			//EIP-75352 Suppress the warnings from static code analyzer
			if (NULL == BootOrder)
			{
		    	MemFreePointer((VOID **) &devOrder);
				return;
			}
			for(i=0;i<size/2;i++)
			{
				bootData = BootGetBootData(BootOrder[i]);
				//EIP-75352 Suppress the warnings from static code analyzer
				if (NULL == bootData)
				{
			    	MemFreePointer((VOID **) &BootOrder);
    				MemFreePointer((VOID **) &devOrder);
					return;
				}
				if ( BBSValidDevicePath(bootData->DevicePath) )
				{                                
					BBS_BBS_DEVICE_PATH *DevPath = (BBS_BBS_DEVICE_PATH *)bootData->DevicePath;
					if((DevPath->DeviceType == DevType) && (bootData->LegacyDevCount == Count))
						break;
				}
			}
			if(i<size/2) //if BootData Found Found
			{
				for(i=0;i<popupSel->ItemCount;i++)
				{
					for(j=0;j<popupSel->ItemCount;j++)
					{
						if(TempDevOrder->Data[i]==bootData->OrderList[j].Index)
						{
							popupSel->PtrTokens[i].Option = HiiAddString( popupSel->ControlData.ControlHandle, bootData->OrderList[j].Name );
							popupSel->PtrTokens[i].Value = bootData->OrderList[j].Index;
							break;
						}
					}
				}
			}
		}
	}
		
    MemFreePointer((VOID **) &BootOrder);
    MemFreePointer((VOID **) &devOrder);

}

#ifdef TSE_FOR_APTIO_4_50
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateLegacyDevVariable
//
// Description:	Update the LegacyDev variable with Device count in each BBS type
//
// Input:		NoOfLegacyGroups
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateLegacyDevVariable(UINT16 NoOfLegacyGroups)
{
	extern EFI_GUID gLegacyDevGuid;
	LEGACY_DEV_LIST	BBSCount = { 0, 0, 0, 0, 0 };
	BBS_ORDER_TABLE *devOrder,*TempDevOrder;
	UINTN i;
	UINTN size = 0;
	UINT16 Count;

	devOrder = VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size );

	for(i=0;i<size;)
	{
		TempDevOrder = (BBS_ORDER_TABLE *)(((UINT8*)devOrder)+i);

		if ( (TempDevOrder->Length >= size) || (0 == TempDevOrder->Length) ) //EIP-120011
		{
			return;
		}
		
		Count = (TempDevOrder->Length/sizeof(UINT16))-1;

		switch(TempDevOrder->Type)
		{
		case BBS_TYPE_FLOPPY:
			BBSCount.FloppyCount = Count ;
			break;
		case BBS_TYPE_HARDDRIVE:
			BBSCount.HardDiskCount = Count ;
			break;
		case BBS_TYPE_CDROM:
			BBSCount.CDROMCount = Count ;
			break;
		case BBS_TYPE_EMBEDDED_NETWORK:
			BBSCount.NetworkCount = Count ;
			break;
		case BBS_TYPE_BEV:
			BBSCount.BevCount = Count ;
			break;
		default:
			break;
		}
		i = i+ sizeof(UINT32)+ TempDevOrder->Length;
	}

    MemFreePointer( (VOID **)&devOrder );
	VarSetNvramName( L"LegacyDev", &gLegacyDevGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &BBSCount, sizeof(BBSCount) );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSUpdateOrder
//
// Description:	Updates the Legacydevorder variable base on the user input
//
// Input:		UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer)
{
	UINTN i,j,k,l;
	UINTN varsize = 0;
	BBS_ORDER_TABLE *devOrder=NULL,*TempDevOrder;
	UINT16 DevCount;

	// TODO
	// Rearrange the legacy dev order Based on the new option
	devOrder =	VarGetVariable( VARIABLE_ID_BBS_ORDER, &varsize  );
	//EIP-75352 Suppress the warnings from static code analyzer
	if (NULL == devOrder)
		return;

	for(i=0;i<varsize ;)
	{
		TempDevOrder = (BBS_ORDER_TABLE *)(((UINT8*)devOrder)+i);

		if ( (TempDevOrder->Length >= varsize) || (0 == TempDevOrder->Length) ) //EIP-120011
		{
			return;
		}

		DevCount = ((TempDevOrder->Length/sizeof(UINT16))-1);
		for(j=0;j<DevCount;j++)
		{
			if(*newOption == TempDevOrder->Data[j]) // Need to update Order for this device type
			{
				// Place the Options in the specific Order.
				for(l=0;l<(*size/sizeof(UINT16));l++)
				{
					for(k=0;k<DevCount;k++)
					{
						if(TempDevOrder->Data[k] == newOption[l])
						{
							TempDevOrder->Data[k] = TempDevOrder->Data[l];
							TempDevOrder->Data[l] = newOption[l];
							break;
						}
					}
				}
				*buffer = devOrder; // return the Real buffer that will be updated.
				*size = varsize;
				return;
			}
		}
		i = i+ sizeof(UINT32)+ TempDevOrder->Length;
	}	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootUpdateOrder
//
// Description:	Updates the boot order variable
//
// Input:		New options, offset, size and Outbuffer
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BootUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **realBuffer)
{
	UINTN varsize = 0;
	UINTN i,j;
	UINT16 * BootOrder;

	BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &varsize );

	for(i=0;i<*size/2;i++)
	{
		for(j=0;j<varsize/2;j++)
		{
			// update the New boot order one by one
			if(BootOrder[j]==newOption[i])
			{
				BootOrder[j]=BootOrder[i];
				BootOrder[i] = newOption[i];
				break;
			}
		}
	}
	*realBuffer = BootOrder;
	*size = varsize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DriverUpdateOrder
//
// Description:	Updates the driver order variable
//
// Input:		New options, offset, size and Outbuffer
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DriverUpdateOrder (UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **realBuffer)
{
	//TSE lite currently not supports driver options
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSELiteFixBootOrderRide
//
// Description:	Function to fix boot override
//
// Input:		CONTROL_DATA *ControlData
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSELiteFixBootOrderRide(CONTROL_DATA *ControlData)
{
    CONTROL_INFO *control;
	UINT16 Index;
	CHAR16 *BootStr;

	control = &(ControlData)->ControlData;

	// Find Boot override Device Index.
	Index = UefiTseLiteGetBootOverRideIndex(control->ControlConditionalPtr);
	if(Index != 0xFFFF)
	{
///EIP - 24971
		BootStr = BootGetBootNowName(Index,(BOOLEAN)gShowAllBbsDev,(BOOLEAN)BootNowInBootOrderSupport());
///EIP - 24971
		UefiSetPromptField(control->ControlPtr,HiiAddString( control->ControlHandle, BootStr ));
		control->ControlHelp = UefiGetPromptField(control->ControlPtr);
	}
}

#ifdef TSE_FOR_APTIO_4_50
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SubMenuHandleSpecialOp
//
// Description:	Sub menu handle for Special operations.
//
// Input:		Submenu data
//
// Output:		Bool - Interpreted by the Caller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _SubMenuHandleSpecialOp( SUBMENU_DATA *submenu )
{
	BOOLEAN status = FALSE;
	UINT32 CtrlCondVariable=0xFFFF, CtrlVariable=0xFFFF;
    CONTROL_INFO *control;
	UINT16 Index;

	control = &submenu->ControlData;

	CtrlCondVariable = GetControlConditionVarId(control);
	CtrlVariable = _GetControlVariable(control);
	
	switch( CtrlCondVariable)
	{	
	case VARIABLE_ID_BOOT_MANAGER:
		// For Boot Override Case
		if( (control->ControlType == CONTROL_TYPE_SUBMENU) && 
			(control->ControlPageID == control->ControlDestPageID) )
		{
			// YES it is boot Over Ride.
			// Find the Index and Try to Boot to it
			Index = UefiTseLiteGetBootOverRideIndex(control->ControlConditionalPtr);
			if(Index != 0xFFFF)
			{
				if(!gResetRequired)
				{
					if(!gDoNotBoot)
					{
    					gApp->ClearScreen = TRUE;
						gST->ConOut->SetAttribute (gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
    					BootLaunchBootNow( Index,(BOOLEAN)gShowAllBbsDev );
     				}
				}
				else
				{
					gApp->Quit = SaveAndReset();
				}
				status = TRUE;
			}
		}

	break;
	case VARIABLE_ID_AMI_CALLBACK:
		if( (control->ControlType == CONTROL_TYPE_SUBMENU) && 
			(control->ControlPageID == control->ControlDestPageID) )
		{
			Index = UefiTseLiteGetAmiCallbackIndex(control->ControlConditionalPtr, control->ControlPtr);
			if(Index != 0xFFFF)
			{
				status = _SubMenuAmiCallback( Index );
			}
		}
	break;
	default:
	break;
	}

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SubMenuAmiCallback
//
// Description:	Function to handle the exit page options.
//
// Input:		UINT16 value
//
// Output:		TRUE/FALSE.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _SubMenuAmiCallback( UINT16 value )
{
	BOOLEAN status = TRUE;

    gApp->Fixed = TRUE;
	switch ( value )
	{
		case SAVE_AND_EXIT_VALUE:
			gApp->Quit = SaveAndExit();
			break;
		case DISCARD_AND_EXIT_VALUE:
			gApp->Quit = ExitApplication();
			break;
		case SAVE_AND_RESET_VALUE:
			gApp->Quit = SaveAndReset();
			break;
		case DISCARD_AND_RESET_VALUE:
			gApp->Quit = ResetSys();
			break;
		case SAVE_VALUE:
			SaveWithoutExit();
			break;
		case DISCARD_VALUE:
			LoadPreviousValues( TRUE );
			break;
		case RESTORE_DEFAULTS_VALUE:
			LoadOptimalDefaults();
			break;
		case SAVE_BOOT_OPTION:
			TseBootAddBootOption();
			break;

		default:
			status = FALSE;
			break;
	}

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordFormCallback
//
// Description:	Function to handle PopupPassword form callbacks.
//
// Input:		CONTROL_INFO * pControlData, UINT16 Key, UINT8 Flags
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordFormCallback(CONTROL_INFO * pControlData, UINT16 Key, UINT8 Flags)
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupEditHandlePassword
//
// Description:	Function to handle PopupEdit password.
//
// Input:		VOID *pPopupEdit, VOID *pData
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupEditHandlePassword( VOID *pPopupEdit, VOID *pData)
{
   	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseLiteIsSpecialOptionList
//
// Description:	Function that decided to re evaluate the option list/Name from the Vfr. 
//				For TSE Special Controls it should return TRUE. for other controls it may return FALSE.
//				For UEFI 2.0 it may return TRUE by default.
//
// Input:		NONE
//
// Output:		Boolean
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TseLiteIsSpecialOptionList(CONTROL_DATA *ControlData)
{	
	UINT32 CtrlCondVariable=0xFFFF, CtrlVariable=0xFFFF;	
	CONTROL_INFO *control;
	
	control = &(ControlData)->ControlData;
	CtrlCondVariable = GetControlConditionVarId(control);
	CtrlVariable = _GetControlVariable(control);

	switch( CtrlCondVariable)
	{	
	case VARIABLE_ID_ADD_BOOT_OPTION:
		if( ( CheckForAddDelBootOption() ) && (control->ControlType == CONTROL_TYPE_POPUPSEL) )
			return TRUE;
		break;
	case VARIABLE_ID_BOOT_MANAGER:
		// For Boot Order Case
		if(( CtrlVariable == VARIABLE_ID_BOOT_ORDER) && 
		((control->ControlType == CONTROL_TYPE_ORDERED_LIST)||(control->ControlType == CONTROL_TYPE_POPUPSEL)))
			return TRUE;
	
		if( ( CheckForAddDelBootOption() ) && 
			( CtrlVariable == VARIABLE_ID_DEL_BOOT_OPTION ) && 
			( control->ControlType == CONTROL_TYPE_POPUPSEL ) )
			return TRUE;
		break;
	case VARIABLE_ID_LEGACY_DEV_INFO:
		if(( CtrlVariable == VARIABLE_ID_BBS_ORDER) && 
		((control->ControlType == CONTROL_TYPE_ORDERED_LIST)||(control->ControlType == CONTROL_TYPE_POPUPSEL)))
			return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostMsgBoxEx
//
// Description:	Function to show messagebox 
//				
// Input:		IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostMsgBoxEx(
IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,
    IN MSGBOX_EX_CATAGORY	MsgBoxExCatagory,
    IN UINT8	 		MsgBoxType,
    IN UINT16			*OptionPtrTokens,	
    IN UINT16	 		OptionCount,		
    IN AMI_POST_MGR_KEY		*HotKeyList, 		
    IN UINT16 			HotKeyListCount, 
    OUT UINT8			*MsgBoxSel,
    OUT AMI_POST_MGR_KEY	*OutKey
)
{
    return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostMsgBox
//
// Description:	Function to show messagebox 
//				
// Input:		IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection)
{
    return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     ShowPostTextBox
//
// Description:  Function to display text entry interface
// 
//
// Input:   IN VOID    *HiiHandle,
//    		IN UINT16 	TitleToken,
//    		IN TEXT_INPUT_TEMPLATE *InputData,
//          IN UINT16 	ItemCount,
//          IN DISPLAY_TEXT_KEY_VALIDATE ValidateKeyFunc
//
// Output: EFI_STATUS 
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostTextBox(
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE FilterKeyFunc
)
{
    return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostMsgBox
//
// Description:	Function to show InfoBox 
//				
// Input:		IN CHAR16  *InfoBoxTitle, IN CHAR16  *Message, IN UINTN   TimeLimit, EFI_EVENT  *RetEvent
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowInfoBox(IN CHAR16  *InfoBoxTitle, IN CHAR16  *Message, IN UINTN   TimeLimit, EFI_EVENT  *RetEvent)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostProgress
//
// Description:	Function to display the progress bar 
//
// Input:	IN UINT8	ProgressBoxState - Progress bar state 
//    		IN CHAR16	*Title		 - Progress bar title 	
//    		IN CHAR16	*Message,	 - Progress bar message string
//    		IN CHAR16	*Legend,	 - Progress bar legend string
//    		IN UINTN 	Percent,	 - Percent Complete (0 - 100)
//    		IN OUT VOID	**Handle,	 - HANDLE. Valid Handle for update and close
//    		OUT AMI_POST_MGR_KEY	*OutKey  - Out Key
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostProgress(
    IN UINT8			ProgressBoxState, 
    IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,	
    IN UINTN 			Percent,	
    IN OUT VOID			**Handle,	
    OUT AMI_POST_MGR_KEY	*OutKey
)
{
    return EFI_UNSUPPORTED;
}

///AMIKeyCode protocol based...
EFI_STATUS _ActionReadKey( AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout );
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionReadKey
//
// Description:	Function to read action key 
//				
// Input:		AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionReadKey (AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout)
{
#if TSE_USE_OEM_ACTION_READ_KEY
	return _OemActionReadKey (pAmiKey, Timeout);
#else
	return _ActionReadKey (pAmiKey, Timeout);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AMIReadKeyStroke
//
// Description:	Function to read key strokes
//				
// Input:		EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AMIReadKeyStroke(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData)
{
	return gST->ConIn->ReadKeyStroke( gST->ConIn, Key );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HelperIsPasswordCharValid
//
// Description:	Function to check for valid password character
//				
// Input:		EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData,UINTN StrIndex,UINTN PasswordLength, CHAR16 *OutChar
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HelperIsPasswordCharValid(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData,UINTN StrIndex,UINTN PasswordLength, CHAR16 *OutChar)
{
	if ( CheckIsAllowedPasswordChar(Key->UnicodeChar) && ( StrIndex < PasswordLength ) )
	{
		*OutChar = Key->UnicodeChar;
		return EFI_SUCCESS;
	}

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsToggleStateKey
//
// Description:	function to check Is any of ToggleStateKey (CapsLock,Numlock ScrollLock) Keys pressed.
//
// Input:		ACTION_DATA *Data
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsToggleStateKey(ACTION_DATA *Data)
{
	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
		// Normal EFI_KEY will return ScanCode and Unicode as 0 for this toggleStateKeys.
		if(Data->Input.Data.AmiKey.Key.ScanCode || Data->Input.Data.AmiKey.Key.UnicodeChar)
			return FALSE;
		else
			return TRUE;
	}
	else
		return FALSE;

}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateBootVariables
//
// Description:	Dummy function for UpdateBootVariables
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateBootVariables ()
{
	// There is some issue with TSE Lite with bellow calls. So adding as a dummy function. 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateDriverVariables
//
// Description:	Dummy function for UpdateDriverVariables
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateDriverVariables ()		//EIP70421 & 70422  Support for driver order
{
	// There is some issue with TSE Lite with bellow calls. So adding as a dummy function. 
}

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
