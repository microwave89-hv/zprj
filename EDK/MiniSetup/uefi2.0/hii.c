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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/hii.c $
//
// $Author: Arunsb $
//
// $Revision: 23 $
//
// $Date: 4/18/13 9:35a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/hii.c $
// 
// 23    4/18/13 9:35a Arunsb
// Dummy functions added to avoid build error in 2.0 build
// 
// 22    3/25/13 8:32a Premkumara
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
// - uefi2.0\HiiCallback.c
// - uefi2.0\hii.h
// - uefi2.0\hii.c 
// 
// 21    10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 17    10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 19    9/25/12 3:04p Arunsb
// RTIfrRegFormNotificationWrapper function call removed
// 
// 17    6/04/11 12:26p Arunsb
// [TAG]            EIP48930 
// [Description]  Boot override hangs with exception 0x0d
// [Files]             uefi2.1\Parse.c, uefi2.0\hii.c
// 
// 16    6/01/11 5:22p Blaines
// [TAG]  		61122
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If SETUP_ORPHAN_PAGES_AS_ROOT_PAGE=1, HiiExit() will cause
// an ASSERT in pool.c if debug_mode is enabled.
// [RootCause]  	HiiExit() exit attempts to free gSetupData elements
// associated with orphaned forms..
// [Solution]  	Only free gSetupData[i].FormSet if
// gSetupData[i].FormSetLength is non-zero.
// [Files]  		Hii.c
// 
// 15    5/31/11 9:51a Premkumara
// [TAG]  		EIP48930 
// [Description]  	Boot override hangs with exception 0x0d
// [Files]  		hii.c, Parse.c
// 
// 14    3/28/11 10:05p Premkumara
// [TAG]  52562  
// [Category] Enhancement 
// [Description] Need to have the Fixed Limit in AMITSE module for
// Controls, Pages and Variable etc.
// [Files]  TSEUefiHii.h, Parse.c, Hii.c, hii.c
// 
// 13    2/10/11 12:32p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 12    2/03/11 3:47p Mallikarjunanv
// Initialized the control flags properly
// 
// 11    2/03/11 1:04p Mallikarjunanv
// Fixed the issue in TSE Lite with respect to setting control info read
// only flags. Which caused issues when selecting some controls.
// 
// 10    2/03/11 12:40p Mallikarjunanv
// [TAG]  		EIP48587
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Press "F3" not loading the optimized defaults for controls
// [RootCause]  	Defaults were not updated properly for UEFI 2.0
// [Solution]  	Updated the defaults values based on controls offsets and
// check box controls are modified as one-of options.
// [Files]  		hii.c
// 
// 9     10/05/10 3:50p Madhans
// [TAG] - EIP 45511 
// [Category]- BUG FIX
// [Severity]- Major 
// [Symptom]- TSE 2.10 with UEFI 2.0 may not work with Runtime Prasing. It
// crashs the system.
// [RootCause]- Initilization of VARIABLE_INFO is affected becaus of UEFI
// 2.1 modifications.
// [Solution]- Initlize the VARIABLE_INFO Strcture with Zero.
// [Files] - hii.c
// 
// 8     7/23/10 5:21p Blaines
// Fix root page processing to support Award Style setup.
// 
// 7     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 11    2/25/10 7:08p Madhans
// To build the defaults with the NVRAM values. This will avoid issues
// caused when defaults load.
// 
// 10    2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 9     2/17/10 11:26p Madhans
// default Var Attribute for the Var store updated to BS+RT+NV
// 
// 8     1/09/10 7:25a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     12/22/09 6:40p Madhans
// // EIP: 32318 fix for the crash issue when the page has many controls.
// 
// 6     8/20/09 3:11p Madhans
// //EIP 25092 : Fix to Use the HiiChangeString() to Add the string for
// morethen one langs.
// 
// 5     8/13/09 7:42a Mallikarjunanv
// modified and moved the function HiiGetEfiKey from binary to uefi module
// 
// 4     7/23/09 8:52a Mallikarjunanv
// updated function InitFormsetLinks for eip-24060
// 
// 3     6/23/09 6:51p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:08p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:14p Madhans
// UEFI Wrapper improvments.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hii.c
//
// Description:	This file contains code to handle the uefi2.0 based hii operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include EFI_PROTOCOL_DEFINITION(Hii)
#include EFI_PROTOCOL_DEFINITION(FormCallback)
extern EFI_HII_PROTOCOL	*gHiiProtocol;

// Maximum supported page, variables, controls.
#define MAX_PAGE 100
#define MAX_CONTROLS 0xFFFF
#define MAX_VARIABLE 100
//---------------------------------------------------------------------------
static VOID*	*gSetupHandles = NULL;
UINTN			gSetupCount = 0;
#pragma pack(1)
typedef struct
{
	UINT8			*FormSet;
	VOID			*Handle;
	UINT16			ClassID;
	UINTN			FormSetLength;
	UINT8			Added;				//To know if this page was present in the tool data
	UINT16			SubClassID;
}
SETUP_LINK;
#pragma pack()

UINTN gDynamicPageCount=0;
static SETUP_LINK *gSetupData = NULL;

static UINT32 ControlListSize, ControlListOffset;

static PAGE_LIST *PageListPtr;
static PAGE_INFO *PageInfoPtr;
static UINT32 PageListSize, PageListOffset, PageInfoSize, PageInfoOffset;

static UINT32 AllocatedFirstPageSize = 0, FirstPageOffset = 0;
static PAGE_INFO *FirstPage = NULL;

EFI_IFR_FORM_SET *HiiGetFormSetFromHandle( /*EFI_HII_HANDLE*/VOID* handle );
EFI_IFR_FORM_SET *HiiGetFormSet( UINTN index );

UINT32 AddControlToList(CONTROL_INFO *NewControlInfo, UINT32 ControlSize);
VOID AddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize);
VOID CreatePage(PAGE_INFO **PageInfo, UINT32 *AllocatedSize, UINT32 *Offset, VOID *Buff, UINT32 BuffSize);
VOID MergePageListAndInfo();


VOID RTIfrProcessExitWrapper(VOID);
VOID RTIfrProcessAddVarListAndPageIDListWrapper(VOID);
BOOLEAN RTIfrProcessFormIfUpdatedWrapper(UINT16 link);
VOID RTIfrProcessRunTimeFormsWrapper(EFI_IFR_REF **ref);

VOID AddDynamicForm(UINT32 HiiIndex);
int AddVariable(EFI_IFR_VARSTORE *Varstore);
VOID AddPageIdToList(PAGE_ID_INFO *NewPageIdInfo, UINT32 PageIdSize);
VOID MergePageIdListAndInfo();
VOID AddVariableToList(VARIABLE_INFO *NewVariableInfo, UINT32 VariableSize);
VOID MergeVariableListAndInfo();
UINTN AddHpkControls(UINT32 HiiIndex, UINT8 *buff,UINTN size, PAGE_INFO **NewPageInfo, UINT32 *AllocatedPageSize, UINT32 *PageOffset);
EFI_STATUS _DisplayErrorMessage(CHAR16 *Temp);

static PAGE_ID_LIST *PageIdListPtr;
static PAGE_ID_INFO *PageIdInfoPtr;
static UINT32 PageIdListSize, PageIdListOffset, PageIdInfoSize, PageIdInfoOffset;

static VARIABLE_LIST *VariableListPtr;
static VARIABLE_INFO *VariableInfoPtr;
static UINT32 VariableListSize, VariableListOffset, VariableInfoSize, VariableInfoOffset;

#define DEFAULT_REFRESH_RATE			0x01
#define DEFAULT_DATETIME_REFRESH		0x05
#define FORM_SUBCLASS 					3
#define	CONTROL_TYPE_TITLE				CONTROL_TYPE_NULL
#define	CONTROL_TYPE_MASK				0x0FFF

#define START_EVAL_IF					0x8000
#define END_EVAL_IF						0x8001

typedef struct PAGELINK
{
  UINT16 FormID;       // number from hpk
  UINT16 ParentPageID; // number from the tool
  UINT16 PageNum;      // number assigned by the tool
	
}PageLink;

typedef struct _VAR_KEY_TABLE
{
	UINT32 VarId;
	UINT16 Index;
	struct _VAR_KEY_TABLE *Next;
}*PVAR_KEY_TABLE, VAR_KEY_TABLE;

VAR_KEY_TABLE	VarKeyTable;

typedef struct FORMSETLINKS
{
	UINT16			PageCount;
	PageLink	PageLink[20];
}FormSetLinks;

FormSetLinks *FSetLinks = NULL;

UINT32 CtrlVar=0, CtrlCondVar=0, CtrlCondVar2=0, ActualCondVar=0, ActualCondVar2=0;
UINT32 controllabel=0,controlindex=0;
UINTN updatecondvars=1;

unsigned short controltypes[] =
{
	CONTROL_TYPE_TITLE,					//#define EFI_IFR_FORM_OP                   0x01
	CONTROL_TYPE_MEMO,					//#define EFI_IFR_SUBTITLE_OP				0x02
	CONTROL_TYPE_TEXT,					//#define EFI_IFR_TEXT_OP					0x03
	0x0,								//#define EFI_IFR_GRAPHIC_OP				0x04
	CONTROL_TYPE_POPUPSEL,				//#define EFI_IFR_ONE_OF_OP					0x05
	CONTROL_TYPE_CHECKBOX,				//#define EFI_IFR_CHECKBOX_OP				0x06
	CONTROL_TYPE_NUMERIC,				//#define EFI_IFR_NUMERIC_OP                0x07
	CONTROL_TYPE_PASSWORD,				//#define EFI_IFR_PASSWORD_OP               0x08
	0x0,								//#define EFI_IFR_ONE_OF_OPTION_OP          0x09    // ONEOF OPTION field
	START_EVAL_IF,						//#define EFI_IFR_SUPPRESS_IF_OP            0x0A
	0x0,								//#define EFI_IFR_END_FORM_OP               0x0B
	0x0,								//#define EFI_IFR_HIDDEN_OP                 0x0C 
	0x0,								//#define EFI_IFR_END_FORM_SET_OP           0x0D
	0x0,								//#define EFI_IFR_FORM_SET_OP               0x0E
	CONTROL_TYPE_SUBMENU,				//#define EFI_IFR_REF_OP                    0x0F
	0x0,								//#define EFI_IFR_END_ONE_OF_OP             0x10
	//0x0,								//#define EFI_IFR_END_OP                    EFI_IFR_END_ONE_OF_OP
	INCONSISTENT_IF,						//#define EFI_IFR_INCONSISTENT_IF_OP        0x11
	0x0,								//#define EFI_IFR_EQ_ID_VAL_OP              0x12
	0x0,								//#define EFI_IFR_EQ_ID_ID_OP               0x13
	0x0,								//#define EFI_IFR_EQ_ID_LIST_OP             0x14
	0x0,								//#define EFI_IFR_AND_OP                    0x15
	0x0,								//#define EFI_IFR_OR_OP                     0x16
	0x0,								//#define EFI_IFR_NOT_OP                    0x17
	END_EVAL_IF,						//#define EFI_IFR_END_IF_OP                 0x18  // for endif of inconsistentif, suppressif, grayoutif
	START_EVAL_IF,						//#define EFI_IFR_GRAYOUT_IF_OP             0x19
	CONTROL_TYPE_DATE,					//#define EFI_IFR_DATE_OP                   0x1A
	CONTROL_TYPE_TIME,					//#define EFI_IFR_TIME_OP                   0x1B
	CONTROL_TYPE_POPUP_STRING,				//#define EFI_IFR_STRING_OP                 0x1C
	0x0,								//#define EFI_IFR_LABEL_OP                  0x1D // defines location where controls can be added
	0x0,								//#define EFI_IFR_SAVE_DEFAULTS_OP          0x1E
	0x0,								//#define EFI_IFR_RESTORE_DEFAULTS_OP       0x1F
	0x0,								//#define EFI_IFR_BANNER_OP                 0x20
	0x0,								//#define EFI_IFR_INVENTORY_OP              0x21
	0x0,								//#define EFI_IFR_EQ_VAR_VAL_OP             0x22
	CONTROL_TYPE_ORDERED_LIST,			//#define EFI_IFR_ORDERED_LIST_OP           0x23
	CONTROL_TYPE_VARSTORE,				//#define EFI_IFR_VARSTORE_OP               0x24
	CONTROL_TYPE_VARSTORE_SELECT,		//#define EFI_IFR_VARSTORE_SELECT_OP        0x25
	CONTROL_TYPE_VARSTORE_SELECT_PAIR,	//#define EFI_IFR_VARSTORE_SELECT_PAIR_OP   0x26
	0x0,								//#define EFI_IFR_LAST_OPCODE               EFI_IFR_VARSTORE_SELECT_PAIR_OP
	0x0,								//#define EFI_IFR_NV_ACCESS_COMMAND         0xFF  
};



UINTN TotalRootPages;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiExit
//
// Description:	performs the operations that required to exit from HII
//
// Input:		VOID
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiExit( VOID )
{
	UINTN i;

	//Remove gSetupHandles
	MemFreePointer((VOID**)&gSetupHandles);

	// Remove memory held by gSetupData
	for ( i = 0; i < gSetupCount; i++ )
    {
		//EIP:61122, Free memory only if gSetupData[i].FormSetLength is non-zero.
        if(gSetupData[i].FormSetLength)
            MemFreePointer(&(gSetupData[i].FormSet));
    }
	MemFreePointer(&gSetupData);
	gSetupCount = 0;
	
	MemFreePointer(&gControlInfo);
	ControlListSize = ControlListOffset = 0;

	MemFreePointer(&gApplicationData);

	gPages = gToolPages;
	PageListPtr = NULL;
	PageInfoPtr = NULL;
	FirstPage = NULL;
	AllocatedFirstPageSize = FirstPageOffset = PageListSize = PageListOffset = PageInfoSize = PageInfoOffset = 0;

	RTIfrProcessExitWrapper();

	gVariables = gToolVariables;
	gPageIdList = gToolPageIdList;
	gPageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[0]);

	return EFI_SUCCESS;
}

VOID FixupPage0ControlInfo( UINTN FormSet, UINTN ControlPtr, VOID* Handle)
{
	PAGE_INFO *pageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList[0]);
	CONTROL_INFO *controlInfo = NULL;
	UINT32 j;

	if(pageInfo->PageControls.ControlCount)
	{
		for ( j = 0; j < pageInfo->PageControls.ControlCount; j++ )
		{
			controlInfo = (CONTROL_INFO*)((UINTN)gToolControlInfo + pageInfo->PageControls.ControlList[j]);
			if( (ControlPtr-FormSet) == (UINTN)controlInfo->ControlPtr )
			{
				controlInfo->ControlHandle = Handle;
				controlInfo->ControlPtr = (VOID*)ControlPtr;
			}
		}
	}

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiFixupData
//
// Description: Function to fixup hhi data
//
// Input:		NIL
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiFixupData( )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32	i, j=0;

	PAGE_INFO	*pageInfo = NULL;
	EFI_IFR_FORM_SET *formSet;
	EFI_IFR_REF *ref = NULL;

	UINT16		link;

	Status = _HiiLocateSetupHandles();
	if ( EFI_ERROR( Status ) )
		return Status;

	gSetupData = EfiLibAllocateZeroPool( sizeof(SETUP_LINK) * gSetupCount );
	if ( gSetupData == NULL )
		return EFI_OUT_OF_RESOURCES;

	for ( i = 0; i < gSetupCount - 1; i++ )
	{
		gSetupData[i].FormSet = _HiiGetForm( gSetupHandles[i], 0, &(gSetupData[i].FormSetLength) );
		if ( gSetupData[i].FormSet == NULL )
		{
			// make sure the handle is also zero
			 gSetupData[i].Handle = 0 ;
			continue;
		}
		gSetupData[i].Handle = gSetupHandles[i];
		formSet = HiiGetFormSet( i );
		gSetupData[i].ClassID = formSet->Class;
		gSetupData[i].SubClassID = formSet->SubClass;

	}

	// need to allocate one more dynamic IFR for the root page, this is NOT a 100% valid
	// formset as there is no form defined
	gSetupData[i].FormSet = EfiLibAllocateZeroPool(
			sizeof(EFI_HII_PACK_HEADER) +
			sizeof(EFI_IFR_FORM_SET) +
			i * sizeof(EFI_IFR_REF)
			);

	formSet = HiiGetFormSet(i);
	MemCopy(&(formSet->Guid),&(gSetupPkg->PackageGuid),sizeof(EFI_GUID));

	TotalRootPages = 0;

	if ( gSetupData[i].FormSet != NULL )
	{
		ref = (EFI_IFR_REF *)(gSetupData[i].FormSet + sizeof(EFI_HII_PACK_HEADER) + sizeof(EFI_IFR_FORM_SET));
		for ( j = 1; j <= gToolPages->PageCount; j++ )
		{
			pageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList[j]);
			if ( pageInfo->PageParentID != 0 ) //if ( pageInfo->PageFormID != 1 ) 
				continue;

			TotalRootPages++;

			link = _HiiGetLinkIndex( &(gToolPageIdInfo[pageInfo->PageIdIndex].PageGuid),
						gToolPageIdInfo[pageInfo->PageIdIndex].PageClass,
						gToolPageIdInfo[pageInfo->PageIdIndex].PageSubClass,
						pageInfo->PageFormID);

			if ( link == (gSetupCount - 1) )
				continue;

			formSet = HiiGetFormSet( link );
			ref->Header.OpCode = EFI_IFR_REF_OP;
			ref->Header.Length = sizeof(EFI_IFR_REF);
			ref->Prompt = formSet->FormSetTitle;
			ref->Help = formSet->Help;
			FixupPage0ControlInfo( (UINTN)gSetupData[i].FormSet, (UINTN)ref, (VOID*)gSetupData[link].Handle);
			ref++;
		}

		gSetupData[i].Handle = gSetupData[0].Handle;

	}

	RTIfrProcessAddVarListAndPageIDListWrapper();

	// update the control (IFR) pointers and HII handles
	for ( i = 0; i< gToolPages->PageCount; i++ )
	{
		PAGE_INFO *NewPageInfo;
		UINT32 PageSize;
		UINT32 ControlSize;
		CONTROL_INFO *NewControlInfo;
		UINTN NoOfControlSpace;

		pageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList[i]);

		if(i == 0)
		{
			link = (UINT16)(gSetupCount - 1);
		}
		else
		{

			link = _HiiGetLinkIndex( &(gToolPageIdInfo[pageInfo->PageIdIndex].PageGuid),
					gToolPageIdInfo[pageInfo->PageIdIndex].PageClass,
					gToolPageIdInfo[pageInfo->PageIdIndex].PageSubClass,
					pageInfo->PageFormID);
		}

		NoOfControlSpace = pageInfo->PageControls.ControlCount ? pageInfo->PageControls.ControlCount - 1 : pageInfo->PageControls.ControlCount;
        	PageSize = (UINT32)(sizeof(PAGE_INFO) + sizeof(pageInfo->PageControls.ControlList) * NoOfControlSpace);
		NewPageInfo = EfiLibAllocateZeroPool(PageSize);

		MemCopy(NewPageInfo,pageInfo,PageSize);

		if ( link == (gSetupCount - 1) )
		{
			NewPageInfo->PageHandle = 0;// This page has been removed in runtime!!!
		}
		else
		{
			if(RTIfrProcessFormIfUpdatedWrapper(link) == TRUE)
				continue;
        	NewPageInfo->PageHandle = gSetupData[link].Handle;
		}

		//Fixup and add the controls in this page to gContolInfo and update offsets in page info
		if(NewPageInfo->PageControls.ControlCount)
		{
		for ( j = 0; j < NewPageInfo->PageControls.ControlCount; j++ )
		{
			CONTROL_INFO	*controlInfo = (CONTROL_INFO *)((UINTN)gToolControlInfo + NewPageInfo->PageControls.ControlList[j]);

			ControlSize = sizeof(CONTROL_INFO) + controlInfo->ControlDataWidth * 2;

			NewControlInfo = EfiLibAllocateZeroPool(ControlSize);
			MemCopy(NewControlInfo, controlInfo, ControlSize);

			if(NewPageInfo->PageHandle != 0)
			{

				NewControlInfo->ControlHandle = gSetupData[link].Handle;

				if ( NewControlInfo->ControlPtr != 0 )
				{
					NewControlInfo->ControlPtr = (VOID*)((UINTN)NewControlInfo->ControlPtr + (UINTN)gSetupData[link].FormSet);
					if ( NewControlInfo->ControlConditionalPtr != 0 )
					{
						NewControlInfo->ControlConditionalPtr = (VOID*)((UINTN)NewControlInfo->ControlConditionalPtr + (UINTN)NewControlInfo->ControlPtr);
					}
				}
				else if ( NewControlInfo ->ControlConditionalPtr != 0 )
				{
					NewControlInfo ->ControlConditionalPtr = (VOID*)((UINTN)NewControlInfo ->ControlConditionalPtr+(UINTN)gSetupData[link].FormSet);
				}
			}

			NewPageInfo->PageControls.ControlList[j] = AddControlToList(NewControlInfo,ControlSize); //Update new offset in gControlInfo

			MemFreePointer(&NewControlInfo);
			}
		}
		else
		{
			// Add the Empty Control to control List even if NewPageInfo->PageControls.ControlCount = 0
			CONTROL_INFO *controlInfo = (CONTROL_INFO*)((UINTN)gToolControlInfo + 0);
			ControlSize = sizeof(CONTROL_INFO) + controlInfo->ControlDataWidth * 2;
			NewControlInfo = EfiLibAllocateZeroPool(ControlSize);
			MemCopy(NewControlInfo, controlInfo, ControlSize);
			AddControlToList(NewControlInfo,ControlSize); //Update new offset in gControlInfo
			MemFreePointer(&NewControlInfo);
		}

		if(i==0)
		{
			CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset, NewPageInfo, PageSize);
		}
		else
		{
			AddPageToList(NewPageInfo,PageSize);
		}
		MemFreePointer(&NewPageInfo);
	}

	RTIfrProcessRunTimeFormsWrapper(&ref);

	MergePageListAndInfo();
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetStringLength
//
// Description:	Function to get the string length
//
// Input:		VOID* handle,
//				UINT16 token
//
// Output:		Length
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token )
{
	CHAR16 *string;
	UINTN length = 0;

	string = HiiGetString( handle, token );
	if ( string == NULL )
		return length;

	length = EfiStrLen( string );
	MemFreePointer( (VOID **)&string );

	return length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiFindHandle
//
// Description:	Function to find the perticular HII handle
//
// Input:		EFI_GUID *guid, UINT16 *index
//
// Output:		Handle
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
/*EFI_HII_HANDLE*/VOID* HiiFindHandle( EFI_GUID *guid, UINT16 *index )
{
	VOID*	*handleBuffer = NULL;
	VOID*	handle = (VOID*)(UINTN)INVALID_HANDLE;

	EFI_IFR_FORM_SET *formSet;
	UINT8 *buffer;

	UINT16 found = 0;
	UINT16 i, count;

	handleBuffer = _HiiGetHandles( &count );
	if ( handleBuffer == NULL )
		return handle;

	for ( i = found = 0; i < count; i++ )
	{
		buffer = _HiiGetForm( handleBuffer[i], 0, NULL );
		if ( buffer == NULL )
			continue;
		formSet = (EFI_IFR_FORM_SET *)(buffer + sizeof(EFI_HII_PACK_HEADER));
		if ( EfiCompareGuid( guid, &formSet->Guid ) )
		{
			if ( *index == found )
			{
				handle = handleBuffer[i];
				(*index)++;
				break;
			}
			found++;
		}

		MemFreePointer( &buffer );
	}

	MemFreePointer( (VOID **)&handleBuffer );
	return handle;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_HiiGetHandles
//
// Description:	Function to get HII handles
//
// Input:		UINT16 *bufferSize
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* * _HiiGetHandles( UINT16 *bufferSize )
{
	EFI_STATUS Status;
	EFI_HII_HANDLE *buffer = NULL;
	UINTN *OutBuf=NULL;
	UINT16 i;

	*bufferSize = 0;
	Status = _HiiWrapperFindHandles( bufferSize, NULL );
	if ( Status != EFI_BUFFER_TOO_SMALL )
		return (VOID*)OutBuf;

	buffer = EfiLibAllocatePool( *bufferSize );
	if ( buffer != NULL )
	{
		Status = _HiiWrapperFindHandles( bufferSize, (VOID**)buffer );
		if ( EFI_ERROR( Status ) )
			MemFreePointer( (VOID **)&buffer );
	}

	*bufferSize /= sizeof(EFI_HII_HANDLE);
	OutBuf = EfiLibAllocatePool( *bufferSize * sizeof(VOID*));

	for(i=0;i<*bufferSize;i++)
		OutBuf[i] = (UINTN)buffer[i];

	MemFreePointer( (VOID **)&buffer );
	
	//return buffer;
	return (VOID*)OutBuf;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_HiiLocateSetupHandles
//
// Description:	Function to find the Setup Handles
//
// Input:		void
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _HiiLocateSetupHandles( VOID )
{
	EFI_STATUS Status;
	UINT16 i = 0;
	UINT16 count;
	/*EFI_HII_HANDLE*/VOID*	*handleBuffer;
	UINT8 *buffer;
	UINT16 found = 0;

	Status = HiiInitializeProtocol();
	if ( EFI_ERROR( Status ) )
		return Status;

	if(FormBrowserLocateSetupHandles(&handleBuffer,&count)!= EFI_SUCCESS)
	{
		handleBuffer = _HiiGetHandles( &count );
	}

	if ( handleBuffer == NULL )
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto _Done;
	}

	gSetupHandles = EfiLibAllocatePool( (count + 1) * sizeof(/*EFI_HII_HANDLE*/VOID*) );
	if ( gSetupHandles == NULL )
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto _Done;
	}

	for ( i = found = 0; i < count; i++ )
	{
		buffer = _HiiGetForm( handleBuffer[i], 0, NULL );
		if ( buffer == NULL )
			continue;
		
		gSetupHandles[found] = handleBuffer[i];
		found++;
		MemFreePointer( &buffer );
	}

	gSetupCount = found + 1;
	// EIP : maximum VFRs supported in TSE
	if(gSetupCount > MAX_PAGE)
	{
		CHAR16 *Temp = L"Reached TSE Maximum supported Page";
		_DisplayErrorMessage(Temp);
		ASSERT(0);
	}

	// at this point we have all the setup specific HII handles into our buffer
_Done:
	if(!FormBrowserHandleValid())
		MemFreePointer( (VOID**)&handleBuffer );

	return Status;	

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetFormSetFromHandle
//
// Description: Function to get formset handle
//
// Input:		VOID* handle
//
// Output:		Formset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_IFR_FORM_SET *HiiGetFormSetFromHandle( /*EFI_HII_HANDLE*/VOID* handle )
{
	UINTN i;

	for ( i = 0; i < gSetupCount; i++ )
	{
		if ( gSetupHandles[i] == handle )
			return HiiGetFormSet( i );
	}

	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetFormSet
//
// Description: Function to get formset
//
// Input:		UINTN index
//
// Output:		formset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_IFR_FORM_SET *HiiGetFormSet( UINTN index )
{
	EFI_IFR_FORM_SET *formSet = NULL;

	if ( index >= gSetupCount )
		return formSet;

	if ( gSetupData == NULL )
		return formSet;

	formSet = (EFI_IFR_FORM_SET*)(gSetupData[index].FormSet + sizeof(EFI_HII_PACK_HEADER));

	return formSet;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_HiiGetForm
//
// Description:	to get data using the input handle
//
// Input:	VOID* handle, UINT16 form, UINTN *Length
//
// Output:	info buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *_HiiGetForm( /*EFI_HII_HANDLE*/VOID* handle, UINT16 form, UINTN *Length )
{
	EFI_STATUS Status;
	VOID *buffer = NULL;

#if HII_VERSION <= 1
	UINT16 bufferSize = 0;
#else
	UINTN bufferSize = 0;	
#endif

	Status = HiiInitializeProtocol();

	if ( EFI_ERROR(Status) )
		return buffer;

	Status = _HiiWrapperGetForm( handle, form, &bufferSize, buffer );
	if ( Status != EFI_BUFFER_TOO_SMALL )
		return buffer;

	buffer = EfiLibAllocatePool( bufferSize );
	if ( buffer == NULL )
		return buffer;

	Status = _HiiWrapperGetForm( handle, form, &bufferSize, buffer );
	if ( EFI_ERROR(Status) )
		MemFreePointer( (VOID **)&buffer );

	if(Length!=NULL)
		*Length = bufferSize;

	return buffer;
}


UINT16 HiiAddStringLanguage( VOID* handle, CHAR16 *lang, CHAR16 *string )
{
	return HiiChangeStringLanguage( handle, 0, lang, string );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiChangeString
//
// Description:	to change a existing string
//
// Input:	VOID* handle, UINT16 token, CHAR16 *string
//
// Output:	Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 HiiChangeString( VOID* handle, UINT16 token, CHAR16 *string )
{
	UINTN i;
	UINT16 returntoken;
	UINT16 status = token;

	for ( i = 0; i < gLangCount; i++ )
    {
   		returntoken = HiiChangeStringLanguage( handle, token, gLanguages[i].Unicode, string );
        if ( token != returntoken )
		{
			//EIP 25092 : Fix to Use the HiiChangeString() to Add the string for morethen one langs.
			//with the same token.
   	        token = status = returntoken;
		}
    }
	return status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsFormFound
//
// Description:	to check whether the perticular form found or not
//
// Input:		EFI_IFR_FORM_SET *formSet,UINT16 formid
//
// Output:		0/1
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 IsFormFound(EFI_IFR_FORM_SET *formSet,UINT16 formid )
{
	UINT8 * RawData = (UINT8 *)formSet;
	while( ((EFI_IFR_OP_HEADER*)RawData)->OpCode != EFI_IFR_END_FORM_SET_OP)
	{
		if(((EFI_IFR_OP_HEADER*)RawData)->OpCode == EFI_IFR_FORM_OP)
			if(((EFI_IFR_FORM*)RawData)->FormId == formid)
				return 1;

		RawData += ((EFI_IFR_OP_HEADER*)RawData)->Length;
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_HiiGetLinkIndex
//
// Description:	to get the index of the link
//
// Input:		EFI_GUID *guid, UINT16 class, UINT16 subclass, UINT16 formid
//
// Output:		Index
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _HiiGetLinkIndex( EFI_GUID *guid, UINT16 class, UINT16 subclass, UINT16 formid )
{
	UINT16	i;
	EFI_IFR_FORM_SET *formSet;
	EFI_HII_PACK_HEADER *pack;

	for ( i = 0; i < gSetupCount - 1; i++ )
	{
		pack = (EFI_HII_PACK_HEADER *)gSetupData[i].FormSet;

		if ( sizeof(EFI_HII_PACK_HEADER) == pack->Length )
			continue;

		formSet = (EFI_IFR_FORM_SET *)((UINT8 *)pack + sizeof(EFI_HII_PACK_HEADER));

		if(EfiCompareGuid( guid , &(formSet->Guid) ))
		{
			if( gSetupData[i].ClassID == class )
			{
				if( gSetupData[i].SubClassID == subclass )
				{
					if(IsFormFound(formSet, formid))
					{
						break;
					}
				}
			}
		}
	}
	return i;
}

EFI_STATUS _HiiWrapperFindHandles( UINT16 *bufferSize, /*EFI_HII_HANDLE*/VOID* *buffer )
{
	return gHiiProtocol->FindHandles( gHiiProtocol, bufferSize, (EFI_HII_HANDLE*)buffer );
}

#if HII_VERSION <= 1
EFI_STATUS _HiiWrapperGetForm( /*EFI_HII_HANDLE*/VOID* handle, UINT16 form, UINT16 *bufferSize, VOID *buffer )
#else
EFI_STATUS _HiiWrapperGetForm( /*EFI_HII_HANDLE*/VOID* handle, UINT16 form, UINTN *bufferSize, VOID *buffer )
#endif
{
	return gHiiProtocol->GetForms( gHiiProtocol,(EFI_HII_HANDLE)(UINTN) handle, form, bufferSize, buffer );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_HiiParseVariablePack
//
// Description:	To parse the variable pack and Update the Current Values with Default Values
//
// Input:		EFI_HII_VARIABLE_PACK_LIST *packList, NVRAM_VARIABLE **pVarList
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _HiiParseVariablePack( EFI_HII_VARIABLE_PACK_LIST *packList, UINT32 offs, UINT32 variable, UINTN size, NVRAM_VARIABLE **pVarList )
{
	EFI_HII_VARIABLE_PACK *pack;
	UINT32 	index;
	UINTN	offset;
    NVRAM_VARIABLE *varList = *pVarList;
	NVRAM_VARIABLE *varPtr;
	UINT8 *srcBuffer;

	for ( ; packList != NULL; packList = packList->NextVariablePack )
	{
		pack = packList->VariablePack;
		if ( pack == NULL )
			continue;

		if ( VarGetVariableInfoId( pack->VariableId, &index ) == NULL )
			continue;

		offset = sizeof(EFI_HII_VARIABLE_PACK) + pack->VariableNameLength;	
//--> EIP:48587
		if( index == variable)
		{
			varPtr = &(varList[index]);
			if ( offs + size > varPtr->Size )
			{
				UINT8 *pnewBuffer;		
				pnewBuffer = EfiLibAllocateZeroPool( offs + size );
				MemCopy( pnewBuffer, varPtr->Buffer, varPtr->Size );
				MemFreePointer( (VOID **)&varPtr->Buffer );
				varPtr->Buffer = pnewBuffer;
				varPtr->Size = offs + size;
			}			
			srcBuffer = (UINT8 *)pack + offset;			
		    if( variable == pack->VariableId ) 
			{
				// Update the Current Values with Defaults values
				MemCopy( &varPtr->Buffer[offs], &srcBuffer[offs], size );
			}
		}// <-- EIP:48587
	}	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiLoadDefaults
//
// Description:	function to load the default values
//
// Input:		NVRAM_VARIABLE **varList, UINTN Mask
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiLoadDefaults( NVRAM_VARIABLE **varList, UINTN Mask )
{
	EFI_STATUS ReturnStatus = EFI_OUT_OF_RESOURCES;
	EFI_STATUS Status;
 	NVRAM_VARIABLE *defaultVar = NULL;
	UINT32 i = 0,  index = 0; // EIP:48587
	UINT32 control; // EIP:48587

	EFI_HII_VARIABLE_PACK_LIST *VariablePack = NULL;

	if ( ( varList == NULL ) /*|| ( *varList == NULL )*/ )
		return ReturnStatus;

	if( ( ! gVariables ) || ( gVariables->VariableCount == 0 ) )	// fatal error
		while(1);

	*varList = EfiLibAllocateZeroPool( sizeof(NVRAM_VARIABLE) * gVariables->VariableCount );
	if ( *varList == NULL )
		return EFI_OUT_OF_RESOURCES;

	// Get the Current Values for defaults
	defaultVar = ( NVRAM_VARIABLE * )*varList;
	for ( i = 0; i < gVariables->VariableCount; i++, defaultVar++ )
	{
		defaultVar->Buffer = VarGetNvram( i, &defaultVar->Size );
	}

	ReturnStatus = HiiInitializeProtocol();
	if ( EFI_ERROR( ReturnStatus ) )
		return ReturnStatus;

	ReturnStatus = EFI_SUCCESS;
	for ( i = 0; i < gSetupCount - 1; i++ )
	{
		Status = gHiiProtocol->GetDefaultImage(
				gHiiProtocol,
				(EFI_HII_HANDLE)(UINTN)gSetupHandles[i], 
				Mask,
				&VariablePack
				);

		if ( EFI_ERROR( Status ) )
		{
			continue;
		}
// EIP:48587	
		for ( ; index < gPages->PageCount; index++ )
		{
			PAGE_INFO *pageInfo = (PAGE_INFO*)((UINT8 *)gPages + gPages->PageList[index]);			
			   
			if( pageInfo->PageHandle == NULL )
			{
				continue;
			}

			if( pageInfo->PageHandle != gSetupHandles[i] ) // EIP:48587 Find the end of current formset and go to next formset
				break;
			
			for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
			{
				CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);
	
				if ( ( controlInfo->ControlVariable == VARIABLE_ID_LANGUAGE ) || ( controlInfo->ControlVariable == VARIABLE_ID_BOOT_ORDER ) || (controlInfo->ControlVariable == VARIABLE_ID_BBS_ORDER) )
					continue;
	
				if ( controlInfo->ControlDataWidth > 0 )
				{
					VOID *ifrData = controlInfo->ControlPtr;
					UINT32 ControlVarOffset;
	
					if ( ifrData == NULL )
						continue;
	
					ControlVarOffset = UefiGetQuestionOffset(ifrData);
	
					if ( VariablePack != NULL )
						_HiiParseVariablePack( VariablePack, ControlVarOffset, controlInfo->ControlVariable, controlInfo->ControlDataWidth, varList );						
				}
			}
		}
		MemFreePointer( (VOID **)&VariablePack );
	}
// EIP:48587
	
	return ReturnStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddControlToList
//
// Description:	to add a control to list
//
// Input:		CONTROL_INFO *NewControlInfo, UINT32 ControlSize
//
// Output:		offset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 AddControlToList(CONTROL_INFO *NewControlInfo, UINT32 ControlSize)
{
	UINT32 offset;
	UINT32 u32Compensation;

	u32Compensation = (sizeof(UINT64) - (ControlSize%sizeof(UINT64))) % sizeof(UINT64);

	if((ControlListOffset + ControlSize + u32Compensation )> ControlListSize)
	{
		gControlInfo = MemReallocateZeroPool( gControlInfo, ControlListSize, ControlListSize + 4096 ); //Allocate 4k at a time
		//Todo: introduce error case
		ControlListSize+=4096;
	}

	MemCopy((UINT8 *)gControlInfo + ControlListOffset, NewControlInfo, ControlSize);

	offset = ControlListOffset;

	ControlListOffset += (ControlSize + u32Compensation);

	return offset;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddPageToList
//
// Description:	to add a page to list
//
// Input:		PAGE_INFO *NewPageInfo, UINT32 PageSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize)
{
	UINT32 offset;
	UINT32 ReallocSize=4096;

    if( PageInfoPtr == NULL )				//EIP48930 
        PageInfoOffset = PageInfoSize = 0;

	if(PageInfoOffset + PageSize >= PageInfoSize)
	{
		if(ReallocSize < PageSize)
			ReallocSize = (PageSize&0xFFFFF000) + 4096;

		PageInfoPtr = MemReallocateZeroPool( PageInfoPtr, PageInfoSize, PageInfoSize + ReallocSize ); //Allocate 4k at a time
		//Todo: introduce error case
		PageInfoSize+=ReallocSize;
	}

	MemCopy((UINT8 *)PageInfoPtr + PageInfoOffset, NewPageInfo, PageSize);

	offset = PageInfoOffset;

	PageInfoOffset += PageSize;

	if(!PageListPtr)
	{
		PageListSize = 512;
		PageListPtr = EfiLibAllocateZeroPool(PageListSize);
		PageListPtr->PageCount = 1; //Leave space for offset of Page 0
		PageListPtr->PageList[PageListPtr->PageCount] = offset;
		PageListPtr->PageCount++;
		PageListOffset = sizeof(PAGE_LIST)+sizeof(UINT32);
	}
	else
	{
		if(PageListOffset + sizeof(UINT32) >= PageListSize)
		{
			PageListPtr = MemReallocateZeroPool(PageListPtr, PageListSize, PageListSize + 128);
			PageListSize += 128;
		}
		PageListPtr->PageList[PageListPtr->PageCount] = offset;
		PageListPtr->PageCount++;
		PageListOffset += sizeof(UINT32);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CreatePage
//
// Description:	function used to create a page
//
// Input:		PAGE_INFO **PageInfo, UINT32 *AllocatedSize,
//				UINT32 *Offset, VOID *Buff, UINT32 BuffSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreatePage(PAGE_INFO **PageInfo, UINT32 *AllocatedSize, UINT32 *Offset, VOID *Buff, UINT32 BuffSize)
{

	if(!(*AllocatedSize))
	{
		//creating a new page
		*PageInfo = EfiLibAllocateZeroPool(BuffSize);
		*AllocatedSize = BuffSize;
		MemCopy(*PageInfo, Buff, BuffSize);

		if((*PageInfo)->PageControls.ControlCount)
			*Offset = BuffSize;
		else //We have space to store one more offset
			//*Offset = BuffSize - sizeof((*PageInfo)->PageControls.ControlList[0]);
// Fix the Issue with the Packing, Original code was not finding the correct Offset
			*Offset = (UINT32)((UINTN)(&(*PageInfo)->PageControls.ControlList[0]) - (UINTN)(*PageInfo));

	}
	else
	{
		//adding offsets
		if(*Offset + BuffSize >= *AllocatedSize)
		{
			*PageInfo = MemReallocateZeroPool( *PageInfo, *AllocatedSize, *AllocatedSize + 128 ); //Allocate 128 bytes at a time
			//Todo: introduce error case
			*AllocatedSize+=128;
		}
		MemCopy((UINT8 *)(*PageInfo) + *Offset, Buff, BuffSize);

		*Offset += BuffSize;

		(*PageInfo)->PageControls.ControlCount++;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MergePageListAndInfo
//
// Description:	To merge the information
//
// Input:		NIL
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MergePageListAndInfo()
{
	UINTN i;

	gApplicationData = EfiLibAllocateZeroPool(PageListOffset + FirstPageOffset + PageInfoOffset);
	gPages = (PAGE_LIST *) gApplicationData;

	MemCopy(gApplicationData, PageListPtr, PageListOffset);
	MemCopy(gApplicationData + PageListOffset, FirstPage, FirstPageOffset);
	MemCopy(gApplicationData + PageListOffset + FirstPageOffset, PageInfoPtr, PageInfoOffset);

	//Fix Offsets
	i=0;
	gPages->PageList[i] = PageListOffset;
	i++;

	for(; i<gPages->PageCount; i++)
	{
		gPages->PageList[i] += (FirstPageOffset + PageListOffset);
	}

	//Free Temp Memory
	MemFreePointer(&FirstPage);
	MemFreePointer(&PageInfoPtr);
	MemFreePointer(&PageListPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiMyGetStringLength
//
// Description:	user function to get the string length
//
// Input:		VOID* handle, UINT16 token
//
// Output:		Length
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiMyGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token )
{
	CHAR16 *string;
	UINTN length = 0;

	string = HiiGetString( handle, token );
	if ( string == NULL )
		return length;

	length = TestPrintLength( string ) / (NG_SIZE);
	MemFreePointer( (VOID **)&string );

	return length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiMyGetMultiLineStringLength
//
// Description:	returns Max length of the in the paragraph
//
// Input:		Handle and token
//
// Output:		Length
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN HiiMyGetMultiLineStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token )
{
	CHAR16 *string;
	UINTN length = 0,MaxLength=0;
	UINTN i,j;

	string = HiiGetString( handle, token );
	if ( string == NULL )
		return length;

	i=j=0;
	while(string[i])
	{
		// is Newline
		if((string[i]==0x0d)&& (string[i+1]==0x0a))
		{
			string[i]=0x0;
			length = TestPrintLength( &string[j] ) / (NG_SIZE);
			if(length>MaxLength)
				MaxLength = length;
			i+=2;
			j=i;	
		}
		else
			i++;
	}
	length = TestPrintLength( &string[j] ) / (NG_SIZE);
	MemFreePointer( (VOID **)&string );

	if(length>MaxLength)
		MaxLength = length;

	return MaxLength;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessExit
//
// Description:	Function to process ifr exit
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessExit(VOID)
{
	MemFreePointer(&gVariables);
	VariableListPtr = NULL;
	VariableInfoPtr = NULL;
	VariableListOffset = VariableListSize = VariableInfoOffset = VariableInfoSize = 0;
	
	MemFreePointer(&gPageIdList);
	PageIdListPtr = NULL;
	PageIdInfoPtr =  NULL;
	PageIdListOffset = PageIdListSize = PageIdInfoOffset = PageIdInfoSize = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessAddVarListAndPageIDList
//
// Description:	Function to add var list page ID list
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessAddVarListAndPageIDList(VOID)
{
	UINT32	i;

	//Create Variable List
	for(i=0; i < gToolVariables->VariableCount ; i++)
	{
		VARIABLE_INFO *VariableInfo;

		VariableInfo = (VARIABLE_INFO *)((UINT8 *)gToolVariables + gToolVariables->VariableList[i]);

		AddVariableToList(VariableInfo, sizeof(VARIABLE_INFO));
	}

	//Create Page ID list
	for(i=0; i < gToolPageIdList->PageIdCount ; i++)
	{
		PAGE_ID_INFO *PageIdInfo;

		PageIdInfo = (PAGE_ID_INFO *)((UINT8 *)gToolPageIdList + gToolPageIdList->PageIdList[i]);

		AddPageIdToList(PageIdInfo, sizeof(PAGE_ID_INFO));
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessFormIfUpdated
//
// Description:	Fuction to process form if updated
//
// Input:		UINT16 link
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN RTIfrProcessFormIfUpdated(UINT16 link)
{
	UINT32 j;
    //Check if the page has changed during run time
    for(j=0; j < gHpkInfoLength / sizeof(HPK_INFO); j++)
    {
        EFI_HII_PACK_HEADER *pack;

        if(
            (gHpkInfo[j].Class == gSetupData[link].ClassID) &&
            (gHpkInfo[j].SubClass == gSetupData[link].SubClassID)
          )
        {
            pack = (EFI_HII_PACK_HEADER *)gSetupData[link].FormSet;

        	if ( gHpkInfo[j].Length != pack->Length )
    			break;
        }
    }

    if(j < gHpkInfoLength / sizeof(HPK_INFO))
    {
        //This page changed during run time parse again
        if(!gSetupData[link].Added)
            AddDynamicForm(link);
		return TRUE;
    }
	gSetupData[link].Added = 1;

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessRunTimeForms
//
// Description:	Function to process runtime forms
//
// Input:		EFI_IFR_REF **ref
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessRunTimeForms(EFI_IFR_REF **ref)
{
	UINT32 i;
	EFI_IFR_FORM_SET *formSet;
	EFI_GUID 	DynamicPageGuid = DYNAMIC_PAGE_COUNT_GUID;
	UINT16 count = 0;

	for(i = 0; i < gSetupCount - 1; i++)
	{
		if(!(gSetupData[i].Added))
		{
			AddDynamicForm(i);
			if((gSetupData[i].Added))
			{
				formSet = HiiGetFormSet( i );
				(*ref)->Header.OpCode = EFI_IFR_REF_OP;
				(*ref)->Header.Length = sizeof(EFI_IFR_REF);
				(*ref)->Prompt = formSet->FormSetTitle;
				(*ref)->Help = formSet->Help;
				(*ref)++;
    			count++ ; 
			}
		}
	}

	gDynamicPageCount = count ;
	
    //Set Dynamic page count variable
    VarSetNvramName( L"DynamicPageCount", &DynamicPageGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
	MergePageIdListAndInfo();
	MergeVariableListAndInfo();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddPageIdToList
//
// Description:	Function to add page id to list
//
// Input:		PAGE_ID_INFO *NewPageIdInfo, UINT32 PageIdSize
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddPageIdToList(PAGE_ID_INFO *NewPageIdInfo, UINT32 PageIdSize)
{
	UINT32 offset;

	if( PageIdInfoPtr == NULL )			//EIP48930 
        PageIdInfoOffset = PageIdInfoSize = 0;

	if(PageIdInfoOffset + PageIdSize >= PageIdInfoSize)
	{
		PageIdInfoPtr = MemReallocateZeroPool( PageIdInfoPtr, PageIdInfoSize, PageIdInfoSize + 256 ); //Allocate 4k at a time
		//Todo: introduce error case
		PageIdInfoSize+=256;
	}

	MemCopy((UINT8 *)PageIdInfoPtr + PageIdInfoOffset, NewPageIdInfo, PageIdSize);

	offset = PageIdInfoOffset;

	PageIdInfoOffset += PageIdSize;

	if(!PageIdListPtr)
	{
		PageIdListSize = 128;
		PageIdListPtr = EfiLibAllocateZeroPool(PageIdListSize);
		PageIdListPtr->PageIdList[PageIdListPtr->PageIdCount] = offset;
		PageIdListPtr->PageIdCount = 1;
		PageIdListOffset = sizeof(PAGE_ID_LIST);
	}
	else
	{
		if(PageIdListOffset + sizeof(UINT32) >= PageIdListSize)
		{
			PageIdListPtr = MemReallocateZeroPool(PageIdListPtr, PageIdListSize, PageIdListSize + 128);
			PageIdListSize += 128;
		}
		PageIdListPtr->PageIdList[PageIdListPtr->PageIdCount] = offset;
		PageIdListPtr->PageIdCount++;
		PageIdListOffset += sizeof(UINT32);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MergePageIdListAndInfo
//
// Description:	Function to merge page id list and info
//
// Input:		NIL
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MergePageIdListAndInfo()
{
	UINTN i;

	gPageIdList = EfiLibAllocateZeroPool(PageIdListOffset + PageIdInfoOffset);
	
	MemCopy(gPageIdList,PageIdListPtr,PageIdListOffset);
	MemCopy(((UINT8 *)gPageIdList)+ PageIdListOffset,PageIdInfoPtr,PageIdInfoOffset);

	for(i=0; i<gPageIdList->PageIdCount; i++)
	{
		gPageIdList->PageIdList[i] += PageIdListOffset;
	}

	gPageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[0]);

	//Free Temp Memory
	MemFreePointer(&PageIdInfoPtr);
	MemFreePointer(&PageIdListPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddVariableToList
//
// Description:	Function to add variable to list
//
// Input:		VARIABLE_INFO *NewVariableInfo, UINT32 VariableSize
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddVariableToList(VARIABLE_INFO *NewVariableInfo, UINT32 VariableSize)
{
	UINT32 offset;

	if(VariableInfoOffset + VariableSize >= VariableInfoSize)
	{
		VariableInfoPtr = MemReallocateZeroPool( VariableInfoPtr, VariableInfoSize, VariableInfoSize + 256 ); //Allocate 4k at a time
		//Todo: introduce error case
		VariableInfoSize+=256;
	}

	MemCopy((UINT8 *)VariableInfoPtr + VariableInfoOffset, NewVariableInfo, VariableSize);

	offset = VariableInfoOffset;

	VariableInfoOffset += VariableSize;

	if(!VariableListPtr)
	{
		VariableListSize = 128;
		VariableListPtr = EfiLibAllocateZeroPool(VariableListSize);
		VariableListPtr->VariableList[VariableListPtr->VariableCount] = offset;
		VariableListPtr->VariableCount = 1;
		VariableListOffset = sizeof(VARIABLE_LIST);
	}
	else
	{
		if(VariableListOffset + sizeof(UINT32) >= VariableListSize)
		{
			VariableListPtr = MemReallocateZeroPool(VariableListPtr, VariableListSize, VariableListSize + 128);
			VariableListSize += 128;
		}
		VariableListPtr->VariableList[VariableListPtr->VariableCount] = offset;
		VariableListPtr->VariableCount++;
		if(VariableListPtr->VariableCount >= MAX_VARIABLE)
		{
			CHAR16 *Temp = L"Reached TSE Maximum supported variables";
			_DisplayErrorMessage(Temp);
			ASSERT(0);
		}
		VariableListOffset += sizeof(UINT32);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MergeVariableListAndInfo
//
// Description:	Function to merge variable list and info
//
// Input:		NIL
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MergeVariableListAndInfo()
{
	UINTN i;

	gVariables = EfiLibAllocateZeroPool(VariableListOffset + VariableInfoOffset);
	
	MemCopy(gVariables,VariableListPtr,VariableListOffset);
	MemCopy(((UINT8 *)gVariables)+ VariableListOffset,VariableInfoPtr,VariableInfoOffset);

	for(i=0; i<gVariables->VariableCount; i++)
	{
		gVariables->VariableList[i] += VariableListOffset;
	}

	//Free Temp Memory
	MemFreePointer(&VariableInfoPtr);
	MemFreePointer(&VariableListPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSubFormCount
//
// Description: function to count the subform and Ref inside the formset.
//
//  Input:		UINT8 *buff	- Pointer to form to search for links to other forms
//
//	Output:		count - no of subforms 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN GetSubFormCount(UINT8 *buff)
{
	UINTN *tmpFormIDBuf; 
	UINTN MaxPagecount=100;
	UINTN PageCount= 0;
	UINTN i=0, j=0, found =0;
	EFI_IFR_OP_HEADER *Header;
	  
	tmpFormIDBuf = (UINTN*)EfiLibAllocateZeroPool(MaxPagecount*sizeof(UINTN));
	//go thru the forms and get the links, creating the lookup table also
	do
	{
		Header = (EFI_IFR_OP_HEADER*)(buff+i);
		switch(Header->OpCode )
		{
            case EFI_IFR_FORM_OP: // find parent in lookup table and then the parent pageNum  to link
				// Add page if is not in lookup table already
				found=0;
				j=0;

				while( (found==0) && ( j < PageCount ) ){
					if(tmpFormIDBuf[j] == ((EFI_IFR_FORM*)Header)->FormId  )
					{
						found =1;
						break;
					}
					j++;
				}

				if(!found)
				{
					// pages in the root(no parent)
					tmpFormIDBuf[PageCount] = ((EFI_IFR_FORM*)Header)->FormId ;
					PageCount++;
				}

		         break;

			case EFI_IFR_REF_OP: // add to lookup table adding the PageID and ParentPageID
                // Add page if is not in lookup table already
				found=0;
				j=0;

				while( (found==0) && ( j < PageCount ) ){
					if(tmpFormIDBuf[j] == ((EFI_IFR_FORM*)Header)->FormId  )
					{
						found =1;
					}
					j++;
				}

				if(!found)
				{
					// pages in the root(no parent)
					tmpFormIDBuf[PageCount] = ((EFI_IFR_FORM*)Header)->FormId ;
					PageCount++;
				}
		       break;

			default:
		      break;
		}
		// If the Buffer is not enough the reallocate more
		if(PageCount >= MaxPagecount)
		{ 
			UINTN *tmpBuf;
			MaxPagecount +=50;
			tmpBuf = (UINTN*)EfiLibAllocateZeroPool(MaxPagecount*sizeof(UINTN));
			MemCopy(tmpBuf,tmpFormIDBuf,sizeof(UINTN)*PageCount);
			MemFreePointer(&tmpFormIDBuf);
			tmpFormIDBuf = tmpBuf;
		}

       i+=Header->Length;
	}while(Header->OpCode != EFI_IFR_END_FORM_SET_OP);

	MemFreePointer(&tmpFormIDBuf);
	return PageCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitFormsetLinks
//
// Description:	Function to init formset links
//
// Input:		char *buff, UINTN InitFormNum
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitFormsetLinks(char *buff,UINTN InitFormNum)
{
	UINTN i=0, j=0, found =0,InitForm=InitFormNum;
	EFI_IFR_OP_HEADER *Header;
	UINTN count = 0;
///EIP:24060 - Start
	UINT16 RootPageinFormSet=0;
///EIP:24060 - End

	// allocate memory for data
	if(FSetLinks != NULL)
		MemFreePointer(&FSetLinks);

  	count = GetSubFormCount(buff);
	FSetLinks = (FormSetLinks*)EfiLibAllocateZeroPool(sizeof(FormSetLinks) + count * sizeof(PageLink));

	//go thru the forms and get the links, creating the lookup table also
	do
	{
		Header = (EFI_IFR_OP_HEADER*)(buff+i);
		switch(Header->OpCode )
		{
            case EFI_IFR_FORM_OP: // find parent in lookup table and then the parent pageNum  to link

				// Add page if is not in lookup table already
				found=0;
				j=0;

				while( (found==0) && ( j < FSetLinks->PageCount ) ){
					if(FSetLinks->PageLink[j].FormID == ((EFI_IFR_FORM*)Header)->FormId  )
					{
                        FSetLinks->PageLink[j].PageNum = (UINT16)InitForm++; 
						found =1;
						break;
					}
					j++;
				}

				if(!found)
				{
///EIP:24060 - Start
					if(!RootPageinFormSet)
						RootPageinFormSet = ((EFI_IFR_FORM*)Header)->FormId;
///EIP:24060 - End
					// pages in the root(no parent)
					FSetLinks->PageLink[FSetLinks->PageCount].FormID = ((EFI_IFR_FORM*)Header)->FormId ;

                    if(IsOrphanPagesAsRootPage()) 
                    {
    					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = 0;
                    }
                    else
                    {
                        if(RootPageinFormSet == ((EFI_IFR_FORM*)Header)->FormId)
        					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = 0;
                        else
        					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = FSetLinks->PageLink[0].PageNum;
                    }

					FSetLinks->PageLink[FSetLinks->PageCount].PageNum = (UINT16)InitForm++;
					FSetLinks->PageCount++;
				}

		         break;

			case EFI_IFR_REF_OP: // add to lookup table adding the PageID and ParentPageID
                // Add page if is not in lookup table already
				found=0;
				j=0;

				while( (found==0) && ( j < FSetLinks->PageCount ) ){
					if(FSetLinks->PageLink[j].FormID == ((EFI_IFR_FORM*)Header)->FormId  )
					{
///EIP:24060 - Start
						if(RootPageinFormSet != FSetLinks->PageLink[j].FormID)
							if(FSetLinks->PageLink[j].PageNum != (UINT16)InitForm-1) // Parent of the Page can't be same page id.
								FSetLinks->PageLink[j].ParentPageID = (UINT16)InitForm-1;


///EIP:24060 - End
						found =1;
					}
					j++;
				}

				if(!found)
				{
					// sub pages
					FSetLinks->PageLink[FSetLinks->PageCount].FormID = ((EFI_IFR_FORM*)Header)->FormId ;
                    FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = (UINT16)InitForm-1;
                    FSetLinks->PageLink[FSetLinks->PageCount].PageNum = 0;
					FSetLinks->PageCount++;
				}
		       break;

			default:
				
		      break;

		}
       i+=Header->Length;
	}while(Header->OpCode != EFI_IFR_END_FORM_SET_OP);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPageParent
//
// Description: Function to get parent page
//
// Input:		int PageNum
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetPageParent(int PageNum)
{
	UINT16 i=0;

	do{
		if(FSetLinks->PageLink[i].PageNum == PageNum  )
		{
			return (FSetLinks->PageLink[i].ParentPageID ); 
			break;
		}
	}while( i++ < FSetLinks->PageCount  );

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPageIdIndex
//
// Description:	To get the index of a perticular page
//
// Input:		EFI_GUID * FormGuid, UINT16 FormClass, UINT16 FormSubClass
//
// Output:		PageIndex
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetPageIdIndex(EFI_GUID * FormGuid, UINT16 FormClass, UINT16 FormSubClass)
{
	UINT16 i;
	PAGE_ID_INFO *PageId;
	
	if(PageIdListPtr == NULL)
		PageIdListPtr = EfiLibAllocateZeroPool(128);

	//search if this combination exists
	for(i = 0; i < PageIdListPtr->PageIdCount ; i++)
	{
		PageId = (PAGE_ID_INFO *) ((UINT8 *)PageIdInfoPtr + PageIdListPtr->PageIdList[i]);
		if( EfiCompareGuid(FormGuid,&(PageId->PageGuid)) )//Compare Guid
		{
			if(FormClass == PageId->PageClass)//Compare class
			{
				if(FormSubClass == PageId->PageSubClass)//Compare SubClass
				{
					break; //found entry
				}
			}
		}
	}
	
	if(i >= PageIdListPtr->PageIdCount)
	{
		PAGE_ID_INFO NewPageId;

		MemCopy(&(NewPageId.PageGuid),FormGuid,sizeof(EFI_GUID));
		NewPageId.PageClass = FormClass;
		NewPageId.PageSubClass = FormSubClass;
	
		i = (UINT16)PageIdListPtr->PageIdCount;
		AddPageIdToList(&NewPageId, sizeof(PAGE_ID_INFO));
	}
	
	return i;
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddVariable
//
// Description: Function to add variable
//
// Input:		EFI_IFR_VARSTORE *Varstore
//
// Output:		success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
int AddVariable(EFI_IFR_VARSTORE *Varstore)
{
	UINT16 i=0;
	UINTN varfound=0;
	char *str2;
	EFI_GUID *GUID = &(Varstore->Guid);
	VARIABLE_INFO *Variable;
	UINT16 VarName[40];
	PVAR_KEY_TABLE pVarTable;


	str2= (char*)((UINT8*)Varstore +sizeof(EFI_IFR_VARSTORE)); //name

	//Convert to unicode string
	MemSet(VarName, sizeof(VarName), 0);

	i = 0;
	while(*str2)
	{
		VarName[i] = *str2;
		i++;
		str2++;
	}


	// check that the variable is not already in the list
	

	for(i=0; i < VariableListPtr->VariableCount; i++)
	{
		Variable = (VARIABLE_INFO *) ((UINT8 *)VariableInfoPtr + VariableListPtr->VariableList[i]);
		if( EfiCompareGuid(GUID,&(Variable->VariableGuid)) )//Compare Guid
			if(EfiStrCmp(VarName,Variable->VariableName) ==0)
			{
				varfound=1;
				Variable->VariableID = Varstore->VarId;
				break;
			}
	}

	if(!varfound)
	{
		VARIABLE_INFO NewVariable;

        MemSet(&NewVariable,sizeof(VARIABLE_INFO),0);
		NewVariable.VariableID = Varstore->VarId;
		MemCopy((&NewVariable.VariableGuid),&(Varstore->Guid),sizeof(EFI_GUID));
		NewVariable.VariableAttributes = 7;
		EfiStrCpy(NewVariable.VariableName,VarName);

		AddVariableToList(&NewVariable, sizeof(VARIABLE_INFO));
	}

	pVarTable = &VarKeyTable;

	while(pVarTable->Next)
		pVarTable = pVarTable->Next;

	pVarTable->Next = EfiLibAllocateZeroPool(sizeof(VAR_KEY_TABLE));
	pVarTable = pVarTable->Next;

	pVarTable->VarId = Varstore->VarId;
	pVarTable->Index = i;

   return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetVarNumFromVarID
//
// Description: Function to get variable number from var ID
//
// Input:		UINT32 ID
//
// Output:		Variable Index
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetVarNumFromVarID(UINT32 ID)
{
	PVAR_KEY_TABLE pVarTable;

	pVarTable = VarKeyTable.Next;

	while(pVarTable)
	{
		if(pVarTable->VarId == ID)
			return(pVarTable->Index);
		pVarTable = pVarTable->Next;
	}

	return 0;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CleanVarKeyTable
//
// Description:	To clear the key table specific buffers
//
// Input:	NIL
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanVarKeyTable()
{
	PVAR_KEY_TABLE pVarTable;

	pVarTable = VarKeyTable.Next;

	while(pVarTable)
	{
		VarKeyTable.Next = pVarTable->Next;
		MemFreePointer(&pVarTable);
		pVarTable = VarKeyTable.Next;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddFormSetVariable
//
// Description:
//
// Input:	EFI_GUID * VarGuid
//
// Output:	VarCount
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 AddFormSetVariable(EFI_GUID * VarGuid)
{
	VARIABLE_INFO Variable;
	UINT32 i;

	Variable.VariableID = 0;
    MemCopy((&Variable.VariableGuid),VarGuid,sizeof(EFI_GUID));
    Variable.VariableAttributes = 0x7; // BT+RT+NV
	EfiStrCpy(Variable.VariableName,L"Setup");

	i = VariableListPtr->VariableCount;
	AddVariableToList(&Variable, sizeof(VARIABLE_INFO));
	
	return i; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsVarGuidPresent
//
// Description:
//
// Input:	EFI_GUID * VarGuid, int * Index
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
int IsVarGuidPresent(EFI_GUID * VarGuid, int * Index)
{
	UINT32 i=0;
	VARIABLE_INFO *Variable;

	for(i=0; i < VariableListPtr->VariableCount; i++)
	{
		Variable = (VARIABLE_INFO *) ((UINT8 *)VariableInfoPtr + VariableListPtr->VariableList[i]);
		if( EfiCompareGuid(VarGuid,&(Variable->VariableGuid)) )//Compare Guid
			if( (EfiStrCmp(L"Setup",Variable->VariableName) ==0)  || 
				(EfiStrCmp(L"setup",Variable->VariableName) ==0 ))
			{
				*Index = i;
				return 1;
			}
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddDynamicForm
//
// Description:
//
// Input:	UINT32 HiiIndex
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddDynamicForm(UINT32 HiiIndex)
{
	EFI_HII_PACK_HEADER *fset;
	EFI_IFR_FORM_SET *Formset;
	EFI_IFR_FORM *form;

	UINTN x, i=0;
	UINT8 *buff = NULL;

	CONTROL_INFO controlInfo;
	UINT32	ControlOffset;
	UINT32 VarIndex;

	PVAR_KEY_TABLE pVarTable;

	UINT32 AllocatedPageSize , PageOffset;
	PAGE_INFO *NewPageInfo;

	PAGE_INFO TempPage;
	
	x = gSetupData[HiiIndex].FormSetLength;
	buff = (UINT8 *) gSetupData[HiiIndex].FormSet;
	fset = (EFI_HII_PACK_HEADER *)buff;
	

    while(i<x) // Look for formsets
	{
		Formset = (EFI_IFR_FORM_SET *) ((UINTN)fset + sizeof(EFI_HII_PACK_HEADER));

		if((fset->Type == FORM_SUBCLASS) && (Formset->Header.OpCode == EFI_IFR_FORM_SET_OP ))
		{
			if(EFI_IFR_END_FORM_SET_OP == *(buff + sizeof(EFI_HII_PACK_HEADER) + sizeof(EFI_IFR_FORM_SET)))
			{
				// This package has no forms. Processing this further will result in unpredictability.
				break;
			}

			gSetupData[HiiIndex].Added = 1;

			CtrlVar=0,CtrlCondVar=0;  // initialize control variables for every formset
            ActualCondVar =0; ActualCondVar2=0;
		    CtrlCondVar2=0;           // this should not be necessary if vfr compiler would start

			// Check the GUID is updated in the Variable list or not
			VarIndex = 0;
			if(IsVarGuidPresent(&(Formset->Guid), &VarIndex))
				CtrlVar = CtrlCondVar = CtrlCondVar2 = ActualCondVar = ActualCondVar2 = VarIndex;
			else
				CtrlVar = CtrlCondVar = CtrlCondVar2 = ActualCondVar = ActualCondVar2 = AddFormSetVariable(&(Formset->Guid));

			pVarTable = &VarKeyTable;

			while(pVarTable->Next)
				pVarTable = pVarTable->Next;

			pVarTable->Next = EfiLibAllocateZeroPool(sizeof(VAR_KEY_TABLE));
			pVarTable = pVarTable->Next;

			pVarTable->VarId = 0;
			pVarTable->Index = (UINT16)CtrlVar;

	        // with a varstote select/select_pair at the beginning of a formset

		    i= sizeof(EFI_HII_PACK_HEADER) + sizeof(EFI_IFR_FORM_SET);
		    form =(EFI_IFR_FORM*)(buff+i );

		    // create the pages lookup table
			InitFormsetLinks((char*)form, PageListPtr ? PageListPtr->PageCount:1);

			// add NULL control above submenu in main
			ControlOffset = 0;
			CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset, &ControlOffset, sizeof(UINT32));

			// add second null control for splitting the page in 2 halves
			if (TotalRootPages == 7)
			{
				ControlOffset = 0;
				CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset, &ControlOffset, sizeof(UINT32));
			}
			
			// add the submenu control to main form  that points to this form.
			controlInfo.ControlHandle = gSetupData[HiiIndex].Handle;
			controlInfo.ControlVariable = 0;
			controlInfo.ControlConditionalVariable[0] = 0;
			controlInfo.ControlConditionalVariable[1] = 0;
			controlInfo.ControlType = CONTROL_TYPE_SUBMENU;
			controlInfo.ControlPageID = 0;
			controlInfo.ControlDestPageID = PageListPtr ? ((UINT16)PageListPtr->PageCount):1 ;

			controlInfo.ControlFlags.ControlVisible = 1;
			controlInfo.ControlFlags.ControlAccess = 0;
			controlInfo.ControlFlags.ControlReadOnly = 0;
			controlInfo.ControlFlags.ControlReset = 0;
			controlInfo.ControlFlags.Reserved1 = 0;
			controlInfo.ControlFlags.ControlRefresh = 0;
			controlInfo.ControlFlags.Reserved2 = 0;


			controlInfo.ControlHelp = 0;
			controlInfo.ControlLabel = 0;
			controlInfo.ControlIndex = 0;
			controlInfo.ControlLabelCount = 0;
			controlInfo.ControlPtr = (VOID*)((UINTN)gSetupData[HiiIndex].FormSet +
				sizeof(EFI_HII_PACK_HEADER) +
				sizeof(EFI_IFR_FORM_SET) +
				TotalRootPages * sizeof(EFI_IFR_REF));
			controlInfo.ControlConditionalPtr = 0;
			controlInfo.ControlDataLength = 0;
			controlInfo.ControlDataWidth = 0;
			controlInfo.QuestionId = 0;

			ControlOffset = AddControlToList(&controlInfo, sizeof(CONTROL_INFO));
			CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset, &ControlOffset, sizeof(UINT32));

			TotalRootPages++;

			// add forms
			while(i<x)
			{
				while((UINT8)*(buff+i) != EFI_IFR_FORM_OP)
				{
					if((UINT8)*(buff+i) == EFI_IFR_VARSTORE_OP)
						AddVariable((EFI_IFR_VARSTORE*)(buff+i));
					i+= (UINT8)*(buff+i+1);

				}

				form =(EFI_IFR_FORM*)(buff+i );

				AllocatedPageSize = PageOffset = 0;
				NewPageInfo = NULL;

				TempPage.PageHandle = gSetupData[HiiIndex].Handle;
				TempPage.PageIdIndex = GetPageIdIndex(&(Formset->Guid), Formset->Class, Formset->SubClass);
				TempPage.PageFormID = form->FormId;
				TempPage.PageTitle = (UINT16)0;
				TempPage.PageSubTitle = form->FormTitle;
				TempPage.PageID = PageListPtr ? ((UINT16) PageListPtr->PageCount):1;
				TempPage.PageParentID = PageListPtr ? GetPageParent(PageListPtr->PageCount):0;

				TempPage.PageFlags.PageVisible = 0;
				TempPage.PageFlags.PageHelpVisible = 0;
				TempPage.PageFlags.PageDisableHotKeys = 0;
				TempPage.PageFlags.Reserved = 0;

				TempPage.PageVariable = 0;
				TempPage.PageControls.ControlCount = 0;
				TempPage.PageControls.ControlList[0] = 0;

                //Check for Dynamic Page Flag
			    if (TempPage.PageParentID == 0 && IsGroupDynamicPages())			//PageParentID is 0 && SDL token is true
			    {
	    			//then set as dynamic page
				    TempPage.PageFlags.PageDynamic = TRUE ;
				    TempPage.PageFlags.PageVisible = TRUE;
				    
			    }

				// memory for TempPage.PageControls.ControlList[0] will be allocated later when adding controls
				CreatePage(&NewPageInfo, &AllocatedPageSize, &PageOffset, &TempPage, sizeof(PAGE_INFO));

				i += AddHpkControls(HiiIndex,(buff + i),x-i,&NewPageInfo, &AllocatedPageSize, &PageOffset);
				
				AddPageToList(NewPageInfo, PageOffset);
				if(NewPageInfo->PageControls.ControlCount >= MAX_CONTROLS)
				{
					CHAR16 *Temp = L"Reached TSE Maximum supported Controls";
					_DisplayErrorMessage(Temp);
					ASSERT(0);
				}

				MemFreePointer(&NewPageInfo);

				if( *((char*)buff +i) == EFI_IFR_END_FORM_SET_OP)
				{
					controllabel = controlindex = 0;
					if(FSetLinks !=NULL)
					{
						MemFreePointer(&FSetLinks);
						FSetLinks = NULL;
					}
					i+=2; // add the end_formset opcode size
					break; //no more forms in this formset...
				}
			} 
		}
		else // package is NOT EFI_HII_IFR
		{
			//go to next package
			i += fset->Length ;
		}
	}  // end of while loop

	CleanVarKeyTable();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetHelpToken
//
// Description:
//
// Input:	UINT8 *ifr
//
// Output:	token
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetHelpToken( UINT8 *ifr )
{
	EFI_IFR_OP_HEADER *headerPtr = (EFI_IFR_OP_HEADER *)ifr;
	UINT16 token = 0;

	switch ( headerPtr->OpCode )
	{
		case EFI_IFR_TEXT_OP:
			{
				EFI_IFR_TEXT *ptr = (EFI_IFR_TEXT *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_ORDERED_LIST_OP:
			{
				EFI_IFR_ORDERED_LIST *ptr = (EFI_IFR_ORDERED_LIST *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_ONE_OF_OP:
			{
				EFI_IFR_ONE_OF *ptr = (EFI_IFR_ONE_OF *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_CHECKBOX_OP:
			{
				EFI_IFR_CHECK_BOX *ptr = (EFI_IFR_CHECK_BOX *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_DATE_OP:
		case EFI_IFR_TIME_OP:
		case EFI_IFR_NUMERIC_OP:
			{
				EFI_IFR_NUMERIC *ptr = (EFI_IFR_NUMERIC *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_PASSWORD_OP:
			{
				EFI_IFR_PASSWORD *ptr = (EFI_IFR_PASSWORD *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_REF_OP:
			{
				EFI_IFR_REF *ptr = (EFI_IFR_REF *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_STRING_OP:
			{
				EFI_IFR_STRING *ptr = (EFI_IFR_STRING *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_SAVE_DEFAULTS_OP:
			{
				EFI_IFR_SAVE_DEFAULTS *ptr = (EFI_IFR_SAVE_DEFAULTS *)headerPtr;
				token = ptr->Help;
			}
			break;
		case EFI_IFR_INVENTORY_OP:
			{
				EFI_IFR_INVENTORY *ptr = (EFI_IFR_INVENTORY *)headerPtr;
				token = ptr->Help;
			}
			break;
		default:
			break;
	}

	return token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetQuestionToken
//
// Description:
//
// Input:	UINT8 *ifr
//
// Output:	token
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetQuestionToken( UINT8 *ifr )
{
	EFI_IFR_OP_HEADER *headerPtr = (EFI_IFR_OP_HEADER *)ifr;
	UINT16 token = 0;

	switch ( headerPtr->OpCode )
	{
		case EFI_IFR_TEXT_OP:
			{
				EFI_IFR_TEXT *ptr = (EFI_IFR_TEXT *)headerPtr;
				token = ptr->Text;
			}
			break;
		case EFI_IFR_ONE_OF_OP:
			{
				EFI_IFR_ONE_OF *ptr = (EFI_IFR_ONE_OF *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_CHECKBOX_OP:
			{
				EFI_IFR_CHECK_BOX *ptr = (EFI_IFR_CHECK_BOX *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_DATE_OP:
		case EFI_IFR_TIME_OP:
		case EFI_IFR_NUMERIC_OP:
			{
				EFI_IFR_NUMERIC *ptr = (EFI_IFR_NUMERIC *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_PASSWORD_OP:
			{
				EFI_IFR_PASSWORD *ptr = (EFI_IFR_PASSWORD *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_REF_OP:
			{
				EFI_IFR_REF *ptr = (EFI_IFR_REF *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_STRING_OP:
			{
				EFI_IFR_STRING *ptr = (EFI_IFR_STRING *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_SAVE_DEFAULTS_OP:
			{
				EFI_IFR_SAVE_DEFAULTS *ptr = (EFI_IFR_SAVE_DEFAULTS *)headerPtr;
				token = ptr->Prompt;
			}
			break;
		case EFI_IFR_INVENTORY_OP:
			{
				EFI_IFR_INVENTORY *ptr = (EFI_IFR_INVENTORY *)headerPtr;
				token = ptr->Text;
			}
			break;
		case EFI_IFR_SUBTITLE_OP:
			{
				EFI_IFR_SUBTITLE *ptr = (EFI_IFR_SUBTITLE *)headerPtr;
				token = ptr->SubTitle;
			}
			break;
		default:
			break;
	}

	return token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPageNumFromFormID
//
// Description:
//
// Input:	UINTN FormID
//
// Output:	PageNum
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetPageNumFromFormID(UINTN FormID)
{
	UINTN i=0;

	do{
		if(FSetLinks->PageLink[i].FormID == FormID  )
		{
			return (FSetLinks->PageLink[i].PageNum ); 
			break;
		}
	}while( i++ < FSetLinks->PageCount  );

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Updatedefaults
//
// Description: Function to update defsaults
//
// Input:	VOID *Data, UINT16 *size, VOID *Failsafe, VOID *Optimal,
//					struct _CONTROL_FLAGS *ControlFlags
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Updatedefaults( VOID *Data, UINT16 *size, VOID *Failsafe, VOID *Optimal, struct _CONTROL_FLAGS *ControlFlags)
{

	UINT8 Flags=0;
	UINTN i=0;
   

	switch( *((UINT8*)Data) )
	{
		// ------ text --------------
		case EFI_IFR_TEXT_OP: //(only interactive)
			Flags =((EFI_IFR_TEXT*)Data)->Flags;

			if(Flags & EFI_IFR_FLAG_INTERACTIVE)
			{

		       ControlFlags->ControlRefresh = DEFAULT_REFRESH_RATE;
               
			}
			
			if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
               ControlFlags->ControlReset = 1;
		break;

		// ------ ref --------------		
		case EFI_IFR_REF_OP: // uses only interactive , but to signal that a key has to be passed
		     break;          // back to a consumer (this behavior is not defined in TSE as of 5/20/05) 

		// ------ one of --------------
		case EFI_IFR_ONE_OF_OP:
		
			i= sizeof(EFI_IFR_ONE_OF);
			do{
				Flags =((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Flags;
			    
				if(Flags & EFI_IFR_FLAG_INTERACTIVE)
		           ControlFlags->ControlRefresh = DEFAULT_REFRESH_RATE;
				
				if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
                   ControlFlags->ControlReset = 1;

	            if(Flags & EFI_IFR_FLAG_DEFAULT)
				{
					*(UINT16*)Optimal = ((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Value; 
					*size=(UINT16)((EFI_IFR_ONE_OF*)Data)->Width;
				}
			
	            if(Flags & EFI_IFR_FLAG_MANUFACTURING )
				{
					*(UINT16*)Failsafe = ((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Value;
					*size=(UINT16)((EFI_IFR_ONE_OF*)Data)->Width;
				}

				i+=sizeof(EFI_IFR_ONE_OF_OPTION);

			}while(((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Header.OpCode != EFI_IFR_END_ONE_OF_OP);
		   break;

		// ------ checkbox --------------
		case EFI_IFR_CHECKBOX_OP:

			Flags = ((EFI_IFR_CHECK_BOX*) Data)->Flags ;

			if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
                ControlFlags->ControlReset = 1;

			 *size = (UINT16)((EFI_IFR_CHECK_BOX*)Data)->Width /*1*/;
             *(UINT16*)Optimal = 0;
             *(UINT16*)Failsafe = 0;
             if (((EFI_IFR_CHECK_BOX*) Data)->Flags & EFI_IFR_FLAG_DEFAULT) {
                 *(UINT16*)Optimal = 1;
             }
             if (((EFI_IFR_CHECK_BOX*) Data)->Flags & EFI_IFR_FLAG_MANUFACTURING) {
                 *(UINT16*)Failsafe = 1;
             }

			 ControlFlags->ControlRefresh=0;
		break;

		// ------ numeric -------------- 
		case EFI_IFR_NUMERIC_OP:
				ControlFlags->ControlRefresh=0;

			Flags = ((EFI_IFR_CHECK_BOX*) Data)->Flags ;

			if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
                ControlFlags->ControlReset = 1;

			// note: width is defined, but default entry is UINT16 in structure.
			    *size = ((EFI_IFR_NUMERIC*)Data)->Width/*2*/;
				*(UINT16*)Optimal = ((EFI_IFR_NUMERIC*)Data)->Default;
			
				*(UINT16*)Failsafe = ((EFI_IFR_NUMERIC*)Data)->Default;
			
			break;

		// ------ ordered list --------------
		case EFI_IFR_ORDERED_LIST_OP:
			i= sizeof(EFI_IFR_ORDERED_LIST);
			do{
				Flags =((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Flags;
			    
				if(Flags & EFI_IFR_FLAG_INTERACTIVE)
		           ControlFlags->ControlRefresh = DEFAULT_REFRESH_RATE;
				
				if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
                    ControlFlags->ControlReset = 1;

	            if(Flags & EFI_IFR_FLAG_DEFAULT)
				{
					*size=(UINT16)((EFI_IFR_ONE_OF*)Data)->Width/*2*/;
					*(UINT16*)Optimal = ((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Value; 
				}
			
	            if(Flags & EFI_IFR_FLAG_MANUFACTURING )
				{
					*size=(UINT16)((EFI_IFR_ONE_OF*)Data)->Width/*2*/;
					*(UINT16*)Failsafe = ((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Value;
				}

				i+=sizeof(EFI_IFR_ONE_OF_OPTION);

			}while(((EFI_IFR_ONE_OF_OPTION*)((char*)Data+i))->Header.OpCode != EFI_IFR_END_ONE_OF_OP);
		   break;


		// ------ date --------------
		case EFI_IFR_DATE_OP:
            ControlFlags->ControlRefresh = DEFAULT_DATETIME_REFRESH;
			break;

		// ------ time --------------
		case EFI_IFR_TIME_OP:
            ControlFlags->ControlRefresh = DEFAULT_DATETIME_REFRESH;
			break;

        case EFI_IFR_STRING_OP:
            Flags = ((EFI_IFR_STRING*) Data)->Flags;

		    if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
                ControlFlags->ControlReset = 1;
			break;

        case EFI_IFR_PASSWORD_OP:
            Flags = ((EFI_IFR_STRING*) Data)->Flags;

		    if(Flags & EFI_IFR_FLAG_RESET_REQUIRED)
                ControlFlags->ControlReset = 1;
			break;

		default:
			break;

	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddHpkControls
//
// Description:
//
// Input:	UINT32 HiiIndex, UINT8 *buff,UINTN size, PAGE_INFO **NewPageInfo,
//					UINT32 *AllocatedPageSize, UINT32 *PageOffset
//
// Output:	UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN AddHpkControls(UINT32 HiiIndex, UINT8 *buff,UINTN size, PAGE_INFO **NewPageInfo, UINT32 *AllocatedPageSize, UINT32 *PageOffset)
{
   UINTN i =0 , end=0,j=0;
   UINTN ConditionalPtr=0, ControlPtr = 0;
   UINT16  DestPageID =0xFFFF, ControlType=0, QuestionId = 0, HelpOffset=0, OpcodeNum = 0;
   BOOLEAN AddControl = TRUE;
   struct _CONTROL_FLAGS ControlFlags ;
   UINTN CtrlFailSafe = 0, CtrlOptimal = 0;
   UINT16 Defaults_size=0;
   EFI_IFR_OP_HEADER *Hdr;
   
   UINT32 ControlSize;
   UINT32	ControlOffset;
   CONTROL_INFO *NewControlInfo;


	// for loop for the number of controls of this
	while(i < size )
 	{
		CtrlFailSafe = 0;
		CtrlOptimal = 0;
				
		MemSet( &ControlFlags, sizeof(CONTROL_FLAGS), 0 );  //reset all the flags to zero
		ControlFlags.ControlVisible =0x1;
/*		ControlFlags.ControlAccess =0;
		ControlFlags.ControlRefresh =0;
		ControlFlags.ControlReset =0;
		ControlFlags.Reserved1 =0;
		ControlFlags.Reserved2 =0;
*/

		// control type
		switch(*(buff +i))
		{
		   case EFI_IFR_END_FORM_OP:
			    controlindex++;
                end =1;
			    break;
			
           default :
			       if(   *(buff +i) == EFI_IFR_LABEL_OP)
				   {
					   UINT8 *tBuff;
					   controllabel ++;
				       controlindex=0;

					   tBuff = (buff +i+ *(buff+i+1));
					   OpcodeNum=0;
					    
					   while( (*tBuff != EFI_IFR_LABEL_OP ) && (*tBuff != EFI_IFR_END_FORM_SET_OP) )
					   {
						   tBuff = tBuff +(unsigned long)*(tBuff+1);
						   OpcodeNum++;
					   };
				   }

				   ControlType = controltypes[*(buff +i) -1];	 
				   HelpOffset = GetHelpToken( buff + i );
				   QuestionId = GetQuestionToken( buff + i );
				   
				   // check if it is 
				   switch(ControlType)
				   {
				     case CONTROL_TYPE_MEMO:
					     break;

				     case CONTROL_TYPE_SUBMENU:
						 DestPageID =  GetPageNumFromFormID(((EFI_IFR_REF*)((char*)buff +i))->FormId);
                         break;

                     case CONTROL_TYPE_CHECKBOX:
						 ControlType = CONTROL_TYPE_POPUPSEL; // With no DestPageID
						 break;

                     case CONTROL_TYPE_POPUPSEL:
						 break;
	
					 case CONTROL_TYPE_TEXT:
						 break;


					 case CONTROL_TYPE_ORDERED_LIST:
						 break;

					 case END_EVAL_IF: // ENDIF for grayout,suppress or inconsistent 
						 ConditionalPtr = 0;
						 updatecondvars =1;

						 AddControl = FALSE;
						 break; 

					 case CONTROL_TYPE_TIME:
						 break;

					 case CONTROL_TYPE_DATE:
						 break;

					 case  CONTROL_TYPE_VARSTORE:
						 AddVariable((EFI_IFR_VARSTORE*)(buff+i));
						 AddControl =FALSE;
						 break;

					 case  CONTROL_TYPE_VARSTORE_SELECT:
                         CtrlVar= ActualCondVar = GetVarNumFromVarID(((EFI_IFR_VARSTORE_SELECT*)((char*)buff +i))->VarId);
						 AddControl =FALSE;
						 break;

 					 case  CONTROL_TYPE_VARSTORE_SELECT_PAIR:
					     CtrlVar= ActualCondVar = GetVarNumFromVarID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)buff +i))->VarId);
					     ActualCondVar2 = GetVarNumFromVarID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)buff +i))->SecondaryVarId);
						 AddControl =FALSE;
						 break;


					 case INCONSISTENT_IF:
					 case START_EVAL_IF: // IF for grayout,suppress or inconsistent 
						 
						 
						 if(updatecondvars == 1)
						 {
							 Hdr= (EFI_IFR_OP_HEADER*) (buff+i);
							 Hdr = (EFI_IFR_OP_HEADER*)((UINT8*)Hdr+Hdr->Length);
							 // special case if there is a varstore just after the IF
							 switch(Hdr->OpCode)
							 {
							 case EFI_IFR_VARSTORE_SELECT_OP:
								 ActualCondVar = GetVarNumFromVarID(((EFI_IFR_VARSTORE_SELECT*)((char*)Hdr))->VarId);
								 break;
							 case EFI_IFR_VARSTORE_SELECT_PAIR_OP:
								 ActualCondVar = GetVarNumFromVarID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)Hdr))->VarId);
							     ActualCondVar2 = GetVarNumFromVarID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)Hdr))->SecondaryVarId);
								 break;

							 }

							 // save CtrlcondVars
                             CtrlCondVar = ActualCondVar;
							 CtrlCondVar2 = ActualCondVar2;
							 updatecondvars = 0;
							 ConditionalPtr = (UINTN)buff+i;
						     
						 }

						 if(ControlType == INCONSISTENT_IF)
						 {
							 AddControl = TRUE;
							 break;
						 }

						 //break; break not used on purpose

					 case 0: // if is not a known control, then go to next control
						 AddControl = FALSE;
						 break;


				   }
			   break;
		}

		if(end ==1)
			break;

		if(AddControl)
		{
			Defaults_size =0;
			Updatedefaults( (void *)(buff + i) , &Defaults_size, &CtrlFailSafe, &CtrlOptimal, &ControlFlags);

			ControlSize = sizeof(CONTROL_INFO) + Defaults_size * 2;

			NewControlInfo = EfiLibAllocateZeroPool(ControlSize);

			ControlPtr =  (UINTN)buff+i;

			if(ControlType == INCONSISTENT_IF)
			{
				ControlType = CONTROL_TYPE_MSGBOX;
				ControlPtr = 0;
			}

			NewControlInfo->ControlHandle = gSetupData[HiiIndex].Handle;
			NewControlInfo->ControlVariable = CtrlVar;
			NewControlInfo->ControlConditionalVariable[0] = CtrlCondVar;
			NewControlInfo->ControlConditionalVariable[1] = CtrlCondVar2;
			NewControlInfo->ControlType = ControlType & CONTROL_TYPE_MASK;
			NewControlInfo->ControlPageID = PageListPtr ? ((UINT16)PageListPtr->PageCount):1;
			NewControlInfo->ControlDestPageID = DestPageID;
			NewControlInfo->ControlFlags = ControlFlags;
			NewControlInfo->ControlHelp = HelpOffset;
			NewControlInfo->ControlLabel = (UINT16)controllabel;
			NewControlInfo->ControlIndex = (UINT16)controlindex;
			NewControlInfo->ControlLabelCount = OpcodeNum;
			NewControlInfo->ControlPtr = (VOID*) ControlPtr;
			NewControlInfo->ControlConditionalPtr = (VOID*)ConditionalPtr;
			NewControlInfo->ControlDataLength = Defaults_size;
			NewControlInfo->ControlDataWidth = Defaults_size;
			NewControlInfo->QuestionId = QuestionId;

			if(Defaults_size !=0)
			{

			  switch(Defaults_size)
			  {
			  case 1: // BYTE
				  *((UINT8 *) ((UINT8 *)NewControlInfo + sizeof(CONTROL_INFO))) = (UINT8)CtrlFailSafe;
				  *((UINT8 *) ((UINT8 *)NewControlInfo + sizeof(CONTROL_INFO) + Defaults_size)) = (UINT8)CtrlOptimal;
				  break;
			  case 2: //WORD
				  *((UINT16 *) ((UINT8 *)NewControlInfo + sizeof(CONTROL_INFO))) = (UINT16)CtrlFailSafe;
				  *((UINT16 *) ((UINT8 *)NewControlInfo + sizeof(CONTROL_INFO) + Defaults_size)) = (UINT16)CtrlOptimal;
				  break;
			  case 4: //DWORD
				  *((UINT32 *) ((UINT8 *)NewControlInfo + sizeof(CONTROL_INFO))) = (UINT32)CtrlFailSafe;
				  *((UINT32 *) ((UINT8 *)NewControlInfo + sizeof(CONTROL_INFO) + Defaults_size)) = (UINT32)CtrlOptimal;
				  break; 
			  }

			}

			ControlOffset = AddControlToList(NewControlInfo, ControlSize);
			CreatePage(NewPageInfo, AllocatedPageSize, PageOffset, &ControlOffset, sizeof(UINT32));

			MemFreePointer(&NewControlInfo);

			if (ControlType & ~ CONTROL_TYPE_MASK)
			{
				ControlOffset = 0;
				CreatePage(NewPageInfo, AllocatedPageSize, PageOffset, &ControlOffset, sizeof(UINT32));
			}

		}
        else
		    AddControl = TRUE;
		
		switch(ControlType)
		{
			case CONTROL_TYPE_POPUPSEL:
			    if( buff[i + sizeof(EFI_IFR_ONE_OF)] == EFI_IFR_ONE_OF_OPTION_OP)
				{
					j = sizeof(EFI_IFR_ONE_OF);
					controlindex+=2; // account for one_of and end_one_of opcodes
                    while(buff[i+j] == EFI_IFR_ONE_OF_OPTION_OP)
					{
						j += sizeof(EFI_IFR_ONE_OF_OPTION);
						controlindex++;
					}
					j += sizeof(EFI_IFR_END_ONE_OF); 
	                break;
				}
				else
				{
					j= *((char*)buff +i+1);  // checkbox
					controlindex++;
				}
                break;

			case CONTROL_TYPE_ORDERED_LIST:
			    if( buff[i + sizeof(EFI_IFR_ORDERED_LIST)] == EFI_IFR_ONE_OF_OPTION_OP)
				{
					j = sizeof(EFI_IFR_ONE_OF);
					controlindex+=2; // account for one_of and end_one_of opcodes
                    while(buff[i+j] == EFI_IFR_ONE_OF_OPTION_OP)
					{
						j += sizeof(EFI_IFR_ONE_OF_OPTION);
						controlindex++;
					}
					j += sizeof(EFI_IFR_END_ONE_OF); 
	                break;
				}

                break;

			case CONTROL_TYPE_TIME:
				j= 3*(*((char*)buff +i+1));
                controlindex+=2;
				break;

			case CONTROL_TYPE_DATE:
				j= 3*(*((char*)buff +i+1));
				controlindex+=2;
				break;

			case CONTROL_TYPE_VARSTORE:
				j= (*((char*)buff +i+1));
				controlindex++;
				break;

			default:
				if( *((char*)buff +i) != EFI_IFR_LABEL_OP)
			       controlindex++;
		        j= *((char*)buff +i+1);

			    break;
		}

	   i= i+ j;
	   DestPageID = 0x0FFFF;
	   ControlType = 0;
	};

	return i+2;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetEfiKey
//
// Description:	Function to Encode the password key
//
// Input:	CHAR16 *PwKey
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HiiGetEfiKey(CHAR16 *PwKey)
{
    EFI_KEY_DESCRIPTOR *pEfiKD = NULL;	//, *pRetEfiKD = NULL;
    UINT16  Count = 0,i;
    EFI_STATUS Status;

    if(EFI_SUCCESS != HiiInitializeProtocol())
        return;

    //Get Count (No Of Key board Desc)
    Status= gHiiProtocol->GetKeyboardLayout(gHiiProtocol, &Count, pEfiKD);

    if(EFI_BUFFER_TOO_SMALL != Status)
        return;

    if(Count)
    {
        //Allocate space for Count number of EFI_KEY_DESCRIPTOR
        pEfiKD = EfiLibAllocateZeroPool(sizeof(EFI_KEY_DESCRIPTOR)*Count);

        Status= gHiiProtocol->GetKeyboardLayout(gHiiProtocol, &Count, pEfiKD);

        if(EFI_SUCCESS == Status)
        {
            for(i=0;i<Count;i++)
            {
                if((pEfiKD[i].Unicode == *PwKey) ||
                    (pEfiKD[i].ShiftedUnicode == *PwKey) ||
                    (pEfiKD[i].AltGrUnicode == *PwKey) ||
                    (pEfiKD[i].ShiftedAltGrUnicode == *PwKey)
                    )
                {
                    *PwKey = (CHAR16)(pEfiKD+i)->Key;
                    break;
                }
            }
        }
        MemFreePointer((VOID **)&pEfiKD);
    }
}
//----------------------------------------------------------------------------
// Procedure:    _DisplayErrorMessage
//
// Description: Function to display Error message when TSE supported limit exceeds
//
//----------------------------------------------------------------------------
EFI_STATUS _DisplayErrorMessage(CHAR16 *Temp)
{
	EFI_EVENT Event;
	EFI_STATUS status = EFI_SUCCESS;;	
	status = PostManagerDisplayInfoBox(L" Unrecoverable Error",Temp,20,&Event);
	if(status)
	{		
		gST->ConOut->OutputString(gST->ConOut,Temp);
	}
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    HiiRemoveString
//
// Description:
//
// Parameter:	    EFI_HII_HANDLE Handle, UINT16 Token
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HiiRemoveString(VOID* Handle, UINT16 Token)
{
  //UEFI2.0 doesn't support
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UefiGetActionWapper
//
// Description:	  The Wrapper function to get the actual action for the driver   	
//
// Parameter:     UINTN Action 
//
// Return Value:  EFI_BROWSER_ACTION 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN UefiGetActionWapper(UINTN Action)
{
   return Action;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     SavePswdString
//
// Description:   Dummy fucntion to avoid build error
//
// Parameter:     CONTROL_INFO * ControlData, CHAR16 *String
//
// Return Value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SavePswdString (CONTROL_INFO *ControlData, CHAR16 *String)
{

}

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
