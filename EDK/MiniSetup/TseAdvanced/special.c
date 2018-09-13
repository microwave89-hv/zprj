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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/special.c $
//
// $Author: Premkumara $
//
// $Revision: 47 $
//
// $Date: 8/28/14 11:49a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/special.c $
// 
// 47    8/28/14 11:49a Premkumara
// [TAG] 			EIP174031
// [Category] 		Improvement
// [Description] 	Removed TODO comments and added proper comments in those
// places
// [Files] 			commonoem.c, commonhelper.c, special.c, submenu.c,
// minisetupext.c, uefi21wapper.c and legacy.c
// 
// 46    5/02/14 12:55p Premkumara
// [TAG]	EIP131549
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	After adding boot/driver options and Loading defaults causes
// crashing issue.
// [Root Cause]	While discarding boot/driver options the boot order get
// corrupted by copying extra data because of wrong size.
// [Solution]	Handled proper size to copy boot/driver options while
// loading defaults
// [Files]	AddBootOption.c, Special.c
// 
// 45    2/11/14 7:47p Arunsb
// [TAG]	EIP140870
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	BBS EFI OS boot entry will not disappear after remove EFI OS
// Hdd.
// [Root Cause]	Once EFI-HDD is removed still NVRAM is giving boot data
// for 
// EFI-HDD(Windows BootManager) with the Active = 0x9(Active+Hidden).
// But TSE is not checking this Active flag for BootOverride menu.
// [Solution]	Checked Boot option for Hidden or Active before creating
// controlInfo
// [Files]	special.c
// 
// 44    12/04/13 2:18p Premkumara
// [TAG]	EIP131549
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	After adding boot/driver options and Loading defaults causes
// crashing issue.
// [Root Cause]	While discarding boot/driver options the boot order get
// corrupted by copying extra data because of wrong size.
// [Solution]	Handled proper size to copy boot/driver options while
// loading defaults
// [Files]	AddBootOption.c, Special.c
// 
// 43    4/11/13 3:36a Arunsb
// [TAG]  		EIP117538
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Boot override of BSU could not see the deivces
// [RootCause]  	Hidden boot devices not handled properly
// [Solution]  	Hidden boot devices included in all boot options display
// related cases.
// [Files]  		special.c
// 
// 42    10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 21    10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 40    9/25/12 5:41a Arunsb
// [TAG]  		EIP100099
// [Category]  	Improvement
// [Description]  	Added submenu icon for driver health options
// [Files]  		special.c
// 
// 39    9/21/12 9:43a Premkumara
//  [TAG]  		EIP 97704
//  [Category]  	Improvement
//  [Description]  	Support BootFFFF variable
//  [Files]  		Boot.h, Boot.c, Special.c
// 
// 38    9/17/12 6:08a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 36    8/29/12 8:43a Premkumara
// [TAG]  		EIP-91817
// [Description]  	To avoid comparing garbage gBootData for
// LoadOptionHidden when SETUP_SHOW_ALL_BBS_DEVICES = 1
// [Files]  		Special.c
// 
// 35    4/03/12 12:40a Premkumara
// [TAG]  		EIP83704
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	HDD user password and Admin password entries are
// disappeared.
// [RootCause]  	When HDD is freeze VARIABLE_ID_IDE_SECURITY variable is
// not updated while navigating to page by page
// [Solution]  	Updated VARIABLE_ID_IDE_SECURITY variable when HDD is
// freeze before navigate to pages.
// [Files]  		Special.c
// 
// 34    1/31/12 6:13a Premkumara
// [TAG]  		EIP79955 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	GEOMETRICSHAPE_RIGHT_TRIANGLE Mark is missing for AddBoot
// option in TSE advanced
// [RootCause]  	Since AddBoot Option is a special control
// GEOMETRICSHAPE_RIGHT_TRIANGLE is not drawn.
// [Solution]  	Drawn GEOMETRICSHAPE_RIGHT_TRIANGLE for AddBoot Option
// control
// [Files]  		Special.c
// 
// 33    1/13/12 1:24a Arunsb
// [TAG]  		EIP80360
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  		HDDSecurity module - Issue in login with TSE, Master
// password disabled
// [RootCause]  	Cache not updated
// [Solution]  	Cache updated properly
// [Files]  		Tseadvanced.c, special.c and uefi21wapper.c
// 
// 32    1/04/12 4:10p Blaines
// [TAG]  		EIP 78627
// [Category]  	Sighting
// [Symptom]  	SAS controller card items in the main list should begin
// with an > (arrow/sideways triagle)
// [RootCause]  	TSE dynamically creates submenu links (controls with the
// SubMenuType = 2, draw without arrow ) to Dynamic Pages (Hii pages
// published by offboard cards with UEFI Option Rom).		
// [Solution]	For Dynamic pages, set the control's property submenu->
// SubMenuType = 1, to draw the control text with an arrow.
// 
// [Files Changed]
// - special.c
// 
// [Functions Changed]
// - _SpecialControlExtras
// 
// 31    12/08/11 9:11p Arunsb
// Wrapper function added for GetFormSetTitleAndHelp fnc to resolve the
// build error in 2.0
// 
// 30    12/01/11 7:16p Blaines
// Fix build errors in Uefi2.0
// 
// 29    11/30/11 1:29p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 28    11/30/11 12:26a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 27    11/13/11 12:38p Arunsb
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
// 26    10/31/11 9:43a Rajashakerg
// [TAG]  		EIP71120,71512 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIOS gets stuck in infinite loop On enabling
// TSE_LOAD_OPTION_HIDDEN token,In first boot incorrect devices is
// disabled in Setup & BBS table but in second boot the correct device is
// disabled in both places.
// [Solution]  	Hidden option handled properly.
// [Files]  		TseLite\variable.c, TseLite\minisetupext.c, TseAdvanced.c,
// special.c, BootOnly\minisetup.h,BootOnly\boot.c, BootOnly\bbs.c
// 
// 25    10/20/11 12:25p Blaines
// Correct the comments.
// 
// 24    10/20/11 11:48a Blaines
// [TAG]  		EIP 72333
// [Category]  	Sighting
// [Symptom]  	Some SAS controller card HII Screen Titles are displaying
// the wrong information
// [RootCause]  	Menu tab always displays the root page title when
// navigating submenu pages. TSE did not support the display of Formset
// Help. 
// 		
// [Solution]	Display Formset Help for Dynamic page, Display page title of
// submenu pages in the menu tab.
// 
// [Files Changed]
// - AMITSE.sdl, CommonHelper.c, special.c, Menu.c, minisetupext.h,
// TseUefiHii.h, Uefi21Wapper.c
// 
// 23    6/30/11 4:12a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Driver health special controls handled.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 22    6/28/11 4:37p Madhans
// [TAG]  		EIP55290
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Keeping Different Default Language other then English will
// cause Lanuage options to show same language repeated.
// [RootCause]  	The Language name was not updated protperly.
// [Solution]  	Fix to read to update  token.
// [Files]  		special.c
// 
// 21    6/20/11 11:50a Rajashakerg
// [TAG]  		EIP59417
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE 
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c 
// 
// 20    6/01/11 4:14p Madhans
// [TAG]  		EIP61588 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	In Advanced page Iscsi page link disappears when any update
// happens
// [RootCause]  	When pages are updated dynamically we might have few
// invalidated PageInfo. Dynamic page grouping special control want not
// checking them
// [Solution]  	Dynamic page grouping special control check if the page is
// valid or not.
// [Files]  		Special.c
// Parse.c
// 
// 19    4/29/11 4:31p Arunsb
// For 2.13 public patch release IFR RefX feature is omitted
// 
// 16    3/23/11 8:38p Blaines
// [TAG] - EIP 23601
// [Category]- Enhancement
// [Symptom]- Add support for OEM special controls.
// [Files] - AmiTse.sdl, CommonHelper.c, Setup.ini, UefiSetup.ini,
// AmiVfr.h, minisetup.h, minisetup.sdl, variable.c, special.c
// 
// 15    3/15/11 5:18a Rajashakerg
// [TAG]  		EIP51671
// [Category]  	New Feature
// [Description]  	Boot overide menu devices are not disable  
// [Files]  		boot.c, minisetup.h, special.c, minisetupext.c, AMITSE.sdl,
// boot.h, CommonHelper.c 
// 
// 14    2/10/11 12:32p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 13    1/10/11 9:36a Mallikarjunanv
// Updated the file with respect to new changes regarding EIP51619
// 
// 12    1/07/11 12:28a Mallikarjunanv
// [TAG]  		EIP51619
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Changing the option in the "HDD BBS Priority" option not
// reflected in the boot options list. 
// [RootCause]  	Boot page is not updated properly with changes made by
// BBS HDD BBS Priority
// [Solution]  	Updated the boot page with changes made by  BBS HDD BBS
// Priority
// [Files]  		special.c, variable.c
// 
// 11    12/25/10 6:44a Mallikarjunanv
// [TAG]  		EIP48391
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BOOT menu string disappeared, and BOOT page not displayed
// properly while adding more than 100 boot options using "Add boot
// option"
// [RootCause]  	if the number of options exceeds the option limit which
// is UINT16, it get crashed
// [Solution]  	Added a new function GetSpecialBootoptionToken(), in which
// by updating the strings in hii for those tokens which are previously
// not updated. If for a token the string is already udpated, we will
// skipt that token.
// [Files]  		special.c
// 
// 10    10/27/10 3:15p Madhans
// [TAG]    	EIP45785
// [Category]	Defect
// [Symptom]	Grayingout the BBS priorities is not working. only supporess
// the first one. for UEFI 2.0
// [RootCause] 	The condition showing only one disabled option is not
// affecting the original condition.
// [Solution]	The control condition will not be updated if it evaluates to
// not COND_NONE.
// [Files]		Special.c
// 
// 9     9/20/10 6:47p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 8     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 15    9/16/10 3:14p Madhans
// To Avoid build issues with TSE_USE_EDK_LIBRARY Building.
// 
// 14    8/27/10 5:04a Mallikarjunanv
// EIP-39334: support to build TSE without the CSM module support
// 
// 13    8/19/10 12:50p Mallikarjunanv
// EIP-42520: Updated to get the BBS group type from the Board module in
// case of a non standard type.
// 
// 12    8/12/10 1:04p Blaines
// Use of reference to gFrame.AddControl to allow option to customization
// outside of
// 
// 11    7/07/10 7:45p Madhans
// Changes to Support Adding Conditions to Suppress or Grayout the Special
// controls.
// 
// 10    4/02/10 4:37p Madhans
// To get ride of TSEOEM.H referance in TSE. Oem hearder files can be
// refered only in Tse Binary.
// 
// 9     3/23/10 5:10p Blaines
// Add new style module hook
// 
// 8     2/19/10 8:12a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/08/10 5:39a Mallikarjunanv
// EIP-34679: Typo error fix
// 
// 6     1/09/10 4:55a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     12/18/09 2:27p Madhans
// EIP: 32350 To fix the Add/Delete Boot option issues with TSE 2.0.
// 
// 4     9/15/09 9:37a Sudhirv
// added support for SETUP_OEM_SPECIAL_CONTROL_SUPPORT and updated the
// Handling of Add Del Boot Option related sources
// 
// 3     8/13/09 7:37a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 2     6/12/09 7:43p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:16p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:27p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Special.c
//
// Description:	This file contains code to handle special Operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include "Special.h"

#define BOOT_OPTION_SIZE sizeof(UINT16)

extern VOID UefiSetHelpField(VOID *IfrPtr,UINT16 Token);
EFI_STATUS GetFormSetTitleAndHelpWrapper (VOID *Handle, UINT16 *Title, UINT16 *Help);
extern BOOLEAN gSetupUpdated;//EIP:51619 Flag which represents the setup update
VOID _SpecialControlExtras(CONTROL_DATA *ctrlData);
VOID _SpecialFixupBootOrder( CONTROL_INFO *control , UINT16 value);
VOID _SpecialFixupLanguages( CONTROL_INFO *control );
VOID _SpecialFixupBBSOrder( CONTROL_INFO *control, UINT16 value );
VOID _SpecialFixupBBSCondition(UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID);
VOID _SpecialFixupBootCondition(UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID);

UINT32 FindVarFromITKQuestionId(UINT16 QuestionId);
VOID _SpecialFixupAddBootOption( CONTROL_INFO *control);
UINT16 GetNoVarStoreBootCountOffset();

UINT16 BBSGetNonStandardGroupType(UINT16 DeviceType);	//EIP-42520

#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
extern UINT16 OEMSpecialGetControlCount(CONTROL_INFO *controlInfo);
extern VOID OEMSpecialOneOfFixup( CONTROL_INFO *control , UINT16 value );
extern VOID OEMSpecialGotoFixup(CONTROL_INFO *control, UINT16 value );
#endif //#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
extern STYLECOLORS  Colors;

//EIP 57661 Driver health support
CHAR16 *FindDriverHealthDriverName (UINT16);
CHAR16 *GetCtrlNameAndHealth (UINT16 ControllerEntry);
//EIP 57661 Ends
//EIP70421 Support for Driver Order starts
VOID	*gDriverPageHandle = NULL;
UINTN 	gDriverOptionTokenCount;
UINT16 	*gDriverOptionTokenArray;
BOOLEAN CheckForAddDelDriverOption (VOID);
VOID _SpecialFixupDriverOrder (CONTROL_INFO *control, UINT16 value);
//EIP70421 Support for Driver Order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialGetIfrPtr
//
// Description:	function to handle the operation of getting the Ifr Pointer.
//
// Input:		VOID* conditional, 
//				UINT32 variable, 
//				GUID_INFO **guidInfo
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *_SpecialGetIfrPtr( CONTROL_INFO *controlInfo, UINT32 * variable, GUID_INFO **guidInfo )
{
    *variable = (UINT32)GetControlConditionVarId(controlInfo);
	return UefiGetSpecialEqIDIfrPtr(controlInfo, variable, guidInfo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialGetValue
//
// Description:	function to handle the operation of getting the Ifr Value.
//
// Input:		CONTROL_DATA *control, 
//				GUID_INFO **guidInfo 
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 SpecialGetValue( CONTROL_DATA *control, GUID_INFO **guidInfo )
{
	return UefiGetSpecialEqIDValue(&control->ControlData, guidInfo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialGetValue
//
// Description:	function to handle the operation of getting the Ifr Value.
//
// Input:		CONTROL_INFO *controlinfo, 
//				GUID_INFO **guidInfo 
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _SpecialGetValue( CONTROL_INFO *controlinfo, GUID_INFO **guidInfo )
{
	return UefiGetSpecialEqIDValue(controlinfo, guidInfo);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialAddControl
//
// Description:	function to Handle adding a control.
//
// Input:		FRAME_DATA *frame , 
//				CONTROL_INFO *controlinfo, 
//				BOOLEAN *SetFocus
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _SpecialAddControl(FRAME_DATA *frame , CONTROL_INFO *ControlInfo, BOOLEAN *SetFocus)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	STYLECOLORS saveColors ;
	

	//Save original style colors
	saveColors = Colors ; 

	//Special control color scheme...
	StyleControlColor(frame, &Colors);
		
	//Adds controls to this frame...
	Status = gFrame.AddControl( frame, ControlInfo  );
	
	//Restore original style colors
	Colors = saveColors;	

	if ( EFI_ERROR(Status) )
		return Status;

	if ( *SetFocus  )
	{
        if ( _FrameSetControlFocus( frame, frame->ControlCount-1 ) )
		{
            frame->CurrentControl = frame->ControlCount-1;
			*SetFocus = FALSE;
		}
	}

	return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoAddBootOptionFixup
//
// Description:	
//
// Input:		CONTROL_INFO *newControlInfo  
//
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoAddBootOptionFixup( CONTROL_INFO *newControlInfo )
{
		_SpecialFixupAddBootOption(newControlInfo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialAddMultipleControls
//
// Description:	Adds Multiple controls for special controls
//
// Input:		FRAME_DATA *frame , CONTROL_INFO *controlInfo, GUID_INFO *guidInfo, BOOLEAN *SetFocus 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialAddMultipleControls( FRAME_DATA *frame , CONTROL_INFO *controlInfo, GUID_INFO *guidInfo, BOOLEAN *SetFocus )
{
	CONTROL_INFO *newControlInfo;
	VARIABLE_INFO *varInfo = NULL;
	UINT8 *dataPtr;
  	VOID *ifrPtr;
	CHAR16 *name = NULL;

	UINT16 count, max = 0, value = 0, HiddenBootOptionCount=0;//EIP : 59417 Declaration for the Hidden Boot option count 
	UINT16 PrevControlQuestionID=0;

	UINT32 varnum=0;
	UINTN condSize;

	if ( frame == NULL )
		return;

	if ( guidInfo->GuidFlags.GuidLaunchCallbackUpdateTemplate )
    {
		UefiSpecialGuidCallback( controlInfo->ControlHandle, 0xFFFE, &guidInfo->GuidValue);
   	}

    varnum = GetControlConditionVarId(controlInfo); //controlInfo->ControlConditionalVariable[0];
    ifrPtr = _SpecialGetIfrPtr( controlInfo, &varnum, NULL ); // TO get the special variable.

  if(NoVarStoreSupport())
  {
    //More info needed.
    if(varnum == VARIABLE_ID_SETUP)
    {
      ifrPtr = _SpecialGetIfrPtr( controlInfo, &varnum, NULL );

      //The variable supplied is setup find the right variable
      varnum = FindVarFromITKQuestionId(UefiGetEqIDQuestionID(ifrPtr));
    }
  }

	if( varnum == VARIABLE_ID_ERROR_MANAGER )  // if it is error manager variable, get the real updated nvram data.
		VarUpdateVariable(varnum);

  	varInfo = ((VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[varnum]));
  	name = GetGUIDNameByID(VARIABLE_ID_LANGUAGE);
    //The following is replaced by Name comparision
    //if ( ((VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[varnum]))->VariableID == LANGUAGE_CODES_KEY_ID )
    if(EfiStrCmp(varInfo->VariableName, name) == 0)
    {
		MemFreePointer(&name);
        max = 1;
    }
    else if (
			(
			CheckForAddDelBootOption () &&
            ((VARIABLE_ID_DEL_BOOT_OPTION  == controlInfo->ControlVariable) || (VARIABLE_ID_ADD_BOOT_OPTION == controlInfo->ControlVariable))
			) ||
			(
			CheckForAddDelDriverOption () &&			//EIP70421 & 70422
            ((VARIABLE_ID_DEL_DRIVER_OPTION == controlInfo->ControlVariable) || (VARIABLE_ID_ADD_DRIVER_OPTION == controlInfo->ControlVariable))
			)
			) 
	{
        max = 1;
	}
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
    else if(varnum == VARIABLE_ID_OEM_TSE_VAR )
	{
        max = OEMSpecialGetControlCount(controlInfo);
	}
#endif
    else
	{
        VarGetValue( varnum, 0, sizeof(UINT16), &max );
	}
	for (count = 0; count < max; count++)
	{
    	if ( ( controlInfo->ControlPtr == 0 ) || ( controlInfo->ControlConditionalPtr == 0 ) )
      		continue;
		if (
			(gLoadOptionHidden && ((VARIABLE_ID_BOOT_MANAGER == varnum) || (VARIABLE_ID_BOOT_NOW == varnum) || (VARIABLE_ID_DRIVER_MANAGER == varnum))) &&
			(VARIABLE_ID_DEL_BOOT_OPTION  != controlInfo->ControlVariable) && 		//For deleting the boot/driver option max is 1 so if first option is hidden nothing will proceed
			(VARIABLE_ID_ADD_BOOT_OPTION != controlInfo->ControlVariable) &&
			(VARIABLE_ID_DEL_DRIVER_OPTION != controlInfo->ControlVariable) && 
			(VARIABLE_ID_ADD_DRIVER_OPTION != controlInfo->ControlVariable)
			)
		{
			if (count < gBootOptionCount)			//EIP-91817 To avoid comparing garbage gBootData for LoadOptionHidden when SETUP_SHOW_ALL_BBS_DEVICES = 1
			{
			 	if ((VARIABLE_ID_DRIVER_MANAGER == varnum) ? (LoadOptionhidden (count, DRIVER_ORDER_OPTION)) : (LoadOptionhidden (count, BOOT_ORDER_OPTION)))
				{
					HiddenBootOptionCount ++; // If the Boot option has the attribute Hidden increment the HiddenBootOptionCount 
					continue;
				}
			}
		}
		newControlInfo = EfiLibAllocatePool( sizeof( CONTROL_INFO ) );
		if ( newControlInfo == NULL )
			continue;

    	MemCopy( newControlInfo, controlInfo, sizeof( CONTROL_INFO ) );
    	condSize = (UINTN)controlInfo->ControlPtr - (UINTN)controlInfo->ControlConditionalPtr;

    	// 256 should be replaced by ControlDataLength, but HPKTool currently does not set it
    	dataPtr = EfiLibAllocateZeroPool( 256 + condSize );
    	if(dataPtr == NULL)
    	{
     	 	MemFreePointer((void**)&newControlInfo);
      		continue;
    	}

		newControlInfo->ControlConditionalPtr = dataPtr;
		MemCopy( dataPtr, (VOID *)controlInfo->ControlConditionalPtr, condSize );
		dataPtr += condSize;
		newControlInfo->ControlPtr = dataPtr;
		MemCopy( dataPtr, (VOID *)controlInfo->ControlPtr, 256 );

		ifrPtr = _SpecialGetIfrPtr( newControlInfo, &varnum, NULL );

		if ( ifrPtr != NULL )
		{
			if ((UefiIsOneOfControl ((VOID *)dataPtr)) && ((VARIABLE_ID_BOOT_MANAGER == varnum) || (VARIABLE_ID_DRIVER_MANAGER == varnum)))
			{
        		UefiSetEqIDValue (ifrPtr, count - HiddenBootOptionCount);
			}
			else
			{
				UefiSetEqIDValue (ifrPtr, count);
			}
		}
		ifrPtr = (VOID *)dataPtr;

		// EIP:51671 START 
		//Depending on the value of the token hide of the disabled boot options is done
		if (gSetupHideDisableBootOptions)
		{
			if(((VARIABLE_ID_BOOT_MANAGER == varnum)||(VARIABLE_ID_BOOT_NOW == varnum))&&(!(UefiIsOneOfControl( ifrPtr ))))
			{		
				if (IsBootDeviceEnabled (count, gShowAllBbsDev, BootNowInBootOrderSupport (), 1))
					continue;
			}
		}
		// EIP:51671 END
		// EIP:59417 START 
		//Checking for the  Bootmanger variable and the token for Load Option hidden
		
		// EIP:59417 END
	    if (UefiIsOneOfControl (ifrPtr))
		{
			UINTN size;
			CHAR16 *newText;
			CHAR16 *text ;

	      	text = HiiGetString( controlInfo->ControlHandle, UefiGetPromptField(ifrPtr) );
			//EIP-75351 Suppress the warnings from static code analyzer
			if (NULL == text) {
				text = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
				if(!text)
					return;
				EfiStrCpy(text,L" ");
	        }
	
			size = sizeof(CHAR16) * ( EfiStrLen( text ) + 10 );
			newText = EfiLibAllocateZeroPool( size );

			SPrint( newText, size, text, count + 1 - HiddenBootOptionCount );
			
			value = _SpecialGetValue( newControlInfo, &guidInfo );
		    UefiSetPromptField(ifrPtr, HiiAddString( controlInfo->ControlHandle, newText ));

			// update boot order , bbs and language tokens, prevent double initialization
			// this code was part of AddControlExtras().
      		UefiUpdateControlVarOffset (newControlInfo->ControlPtr, value * sizeof(UINT16));

       	     switch ( guidInfo->GuidKey )
       	     {
                 case GUID_KEY_BOOT_NOW:
			        if (NoVarStoreSupport())
			        {
			          _SpecialFixupBootOrder (newControlInfo, value);
			        }
			        else
					{
	                    if (newControlInfo->ControlVariable == VARIABLE_ID_BOOT_ORDER)
						{
					          _SpecialFixupBootOrder (newControlInfo, value);
					          //if count not eq to 0 and count-1 Control is Disabled then supress the current control.
							  _SpecialFixupBootCondition(count,newControlInfo,PrevControlQuestionID);
							  PrevControlQuestionID = UefiGetQuestionID(newControlInfo);
						}
	                    else if (newControlInfo->ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION)
	                    {
							TSESpecialFixupDelBootOption (newControlInfo);
	                    }
					}
					break;
                case GUID_KEY_ADD_BOOT_OPTION:
                    if ((CheckForAddDelBootOption()) && (newControlInfo->ControlVariable == VARIABLE_ID_ADD_BOOT_OPTION))
                    {
						UefiUpdateControlVarOffset(newControlInfo->ControlPtr, UefiGetQuestionOffset(controlInfo->ControlPtr));
						TseDoAddBootOptionFixup( newControlInfo );
                    }
					break;
			
				case GUID_KEY_LANG_CODES:
					if ( gLangCount > 0 )
						_SpecialFixupLanguages( newControlInfo );
					break;

				case GUID_KEY_BBS_ORDER:
					_SpecialFixupBBSOrder( newControlInfo, value);
			        if(!NoVarStoreSupport())
			        {
			          //if count not eq to 0 and count-1 Control is Disabled then supress the current control.
			          _SpecialFixupBBSCondition(count,newControlInfo,PrevControlQuestionID);
					  PrevControlQuestionID = UefiGetQuestionID(newControlInfo);
			        }
					break;
				case GUID_KEY_DRIVER_OPTION:			//EIP70421 & 70422
                    if (VARIABLE_ID_DRIVER_ORDER == newControlInfo->ControlVariable)
					{
				          _SpecialFixupDriverOrder (newControlInfo, value);
				          //if count not eq to 0 and count-1 Control is Disabled then supress the current control.
						  _SpecialFixupBootCondition (count, newControlInfo, PrevControlQuestionID);
						  PrevControlQuestionID = UefiGetQuestionID(newControlInfo);
					}
					else if (VARIABLE_ID_DEL_DRIVER_OPTION == newControlInfo->ControlVariable)
					{
						TSESpecialFixupDelDriverOption (newControlInfo);
					}
					break;
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
				case GUID_KEY_OEM_CONTROL:
					// Do the OEM Special Control's OneOf Fixup
					OEMSpecialOneOfFixup( newControlInfo, value);
					break;
#endif
				default:
					break;
			}			

			MemFreePointer( (VOID **)&newText );
			MemFreePointer( (VOID **)&text );
		}
		_SpecialAddControl( frame, newControlInfo, SetFocus );
		// update optional info specially for boot order controls
        _SpecialControlExtras((frame->ControlList[frame->ControlCount-1]));
		MemFreePointer( (VOID **)&newControlInfo );
	}

	gSetupUpdated = FALSE; //EIP:51619 Reset the SetupUpdated Flag here.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupLanguages
//
// Description:	function to fixup the languages
//
// Input:		CONTROL_INFO *control 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupLanguages( CONTROL_INFO *control )
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i,  length = 0;
  	BOOLEAN flag = FALSE;

	ifrPtr = (VOID *)control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);

	if(PlatformLangVerSupport())	
 	 	UefiSetWidth(ifrPtr, 6);
	else
 	 	UefiSetWidth(ifrPtr, 3);

	tempPtr = UefiCreateOneOfWithOptionsTemplate( gLangCount, control );
	if ( tempPtr == NULL )
		return;

	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
  	length = UefiGetIfrLength(templatePtr);
	for ( i = 0; i < gLangCount; i++ )
	{
		MemCopy( oneOf, templatePtr, length );
    	flag = 0;
        gLanguages[i].Token = HiiChangeString( gHiiHandle, gLanguages[i].Token, gLanguages[i].LangString );
    	UefiSetOneOfOption(oneOf, i, BOOT_OPTION_SIZE, flag, gLanguages[i].Token);
    	oneOf = (UINT8*)oneOf +length;
	}

  	// Add an End op to close scope of the One of control
  	UefiAddEndOp(oneOf);

	tempPtr = HiiGetString( control->ControlHandle, UefiGetPromptField(ifrPtr) );
	UefiSetPromptField (control->ControlPtr,HiiAddString( gHiiHandle, tempPtr ));

	MemFreePointer( (VOID **)&tempPtr );
	tempPtr = HiiGetString( control->ControlHandle, UefiGetHelpField(ifrPtr) );

	control->ControlHelp = HiiAddString( gHiiHandle, tempPtr );
	control->ControlHandle = gHiiHandle;

	MemFreePointer( (VOID **)&tempPtr );
}

//EIP-48391: Start

static VOID		*gBootPageHandle = NULL;
static UINTN 	gBootOptionTokenCount;
static UINT16 	*gBootOptionTokenArray;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetSpecialBootoptionToken
//
// Description:	function to get the boot option token properly when loading the boot page
//
// Input:		VOID* handle, UINTN Index
//
// Output:		TOKEN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetSpecialBootoptionToken(VOID* handle, UINTN Index) 
{
	UINTN i;

	// EIP:51619 TO make sure it is called by _SpecialFixupBootOrder() and Boot page not modified
	if (gBootPageHandle == handle)
	{
		if(FALSE == gSetupUpdated)
		{
			if(!gBootOptionTokenCount)
			{
				// Create the gBootOptionTokenArray
				gBootOptionTokenArray = EfiLibAllocateZeroPool (sizeof(UINT16) * gBootOptionCount);
				gBootOptionTokenCount = gBootOptionCount;
				for(i=0;i< gBootOptionTokenCount;i++)
				{
					gBootOptionTokenArray[i] = INVALID_TOKEN;
				}
			}
			else if(gBootOptionTokenCount < gBootOptionCount)
			{ // Boot options added. Update gBootOptionTokenArray
				gBootOptionTokenArray = MemReallocateZeroPool(gBootOptionTokenArray, (sizeof(UINT16) * gBootOptionTokenCount), (sizeof(UINT16) * gBootOptionCount));
				for(i= gBootOptionTokenCount; i< gBootOptionCount ;i++)
				{
					gBootOptionTokenArray[i] = INVALID_TOKEN;
				}
				gBootOptionTokenCount = gBootOptionCount;
			}
			
			if(gBootOptionTokenArray[Index] == INVALID_TOKEN)
				gBootOptionTokenArray[Index] = HiiAddString(handle, BootGetOptionName( &(gBootData[Index]) ) );
            else
            {
                // Check if Update is needed
                CHAR16 *text;
                text = HiiGetString( handle, gBootOptionTokenArray[Index]);
					 
				if (NULL == text) //EIP-131549
					return (UINT16)EFI_OUT_OF_RESOURCES;
						 
                if(EfiStrCmp(text, BootGetOptionName( &(gBootData[Index]) )) != 0)
                {
                    // need to update the token with new BootoptionName.
                    UINT16  Token = HiiChangeString( handle, gBootOptionTokenArray[Index], BootGetOptionName( &(gBootData[Index]) ));
                    if(Token != gBootOptionTokenArray[Index])
                        gBootOptionTokenArray[Index] = Token;
                }
                MemFreePointer((VOID **)&text);
            }
		}
		else {
			//If the some control modified with respect to boot page..
	 		gBootOptionTokenArray[Index] = HiiAddString(handle, BootGetOptionName( &(gBootData[Index]) ) );
		}
		return gBootOptionTokenArray[Index];

	}
	else
		//If the call is not from _SpecialFixupBootOrder() 
	 	return	HiiAddString(handle, BootGetOptionName( &(gBootData[Index]) ) );
}
//EIP-48391: End

//EIP70421 & 70422 Support for Driver Order starts
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------
// Procedure:	_GetSpecialDriveroptionToken
//
// Description:	function to get the boot option token properly when loading the boot page
//
// Input:		VOID* handle, UINTN Index
//
// Output:		TOKEN
//
//-------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetSpecialDriveroptionToken (VOID* handle, UINTN Index) 
{
	UINTN i;

	if (gDriverPageHandle == handle)
	{
		if(FALSE == gSetupUpdated)
		{
			if (!gDriverOptionTokenCount)
			{
				// Create the gDriverOptionTokenArray
				gDriverOptionTokenArray = EfiLibAllocateZeroPool (sizeof(UINT16) * gDriverOptionCount);
				gDriverOptionTokenCount = gDriverOptionCount;
				for (i = 0; i < gDriverOptionTokenCount; i ++)
				{
					gDriverOptionTokenArray [i] = INVALID_TOKEN;
				}
			}
			else if (gDriverOptionTokenCount < gDriverOptionCount)
			{ // Drivers options added. Update gDriverOptionTokenArray
				gDriverOptionTokenArray = MemReallocateZeroPool (gDriverOptionTokenArray, (sizeof (UINT16) * gDriverOptionTokenCount), (sizeof (UINT16) * gDriverOptionCount) );
				for (i = gDriverOptionTokenCount; i < gDriverOptionCount ; i ++)
				{
					gDriverOptionTokenArray [i] = INVALID_TOKEN;
				}
				gDriverOptionTokenCount = gDriverOptionCount;
			}
			
			if (gDriverOptionTokenArray [Index] == INVALID_TOKEN)
				gDriverOptionTokenArray [Index] = HiiAddString (handle, DriverGetOptionName (&(gDriverData [Index]) ) );
			else
            {
                // Check if Update is needed
                CHAR16 *text;
                text = HiiGetString( handle, gDriverOptionTokenArray [Index]);
                if(EfiStrCmp(text, DriverGetOptionName ( &(gDriverData[Index]) )) != 0)
                {
                    // need to update the token with new DriveroptionName.
                    UINT16  Token = HiiChangeString( handle, gDriverOptionTokenArray [Index], DriverGetOptionName( &(gDriverData[Index]) ));
                    if(Token != gDriverOptionTokenArray [Index])
                        gDriverOptionTokenArray [Index] = Token;
                }
                MemFreePointer((VOID **)&text);
            }
		}
		else {
			//If the some control modified with respect to boot page..
	 		gDriverOptionTokenArray [Index] = HiiAddString (handle, DriverGetOptionName (&(gDriverData [Index]) ) );
		}
		return gDriverOptionTokenArray [Index];

	}
	else
		//If the call is not from _SpecialFixupBootOrder() 
	 	return	HiiAddString(handle, DriverGetOptionName (&(gDriverData [Index]) ) );
}
//EIP70421 & 70422 Support for Driver Order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBootOrder
//
// Description:	function to fixup the Boot device order
//
// Input:		CONTROL_INFO *control,
//				UINT16 value	 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBootOrder (CONTROL_INFO *control, UINT16 value)
{
	VOID 	*tempPtr, *ifrPtr;
	VOID 	*templatePtr, *oneOf;
	UINTN 	i;
	CHAR16 	*text;
	UINT8 	length = 0;
	UINT16 	option = 0;
	UINT8 	flag = 0;

	ifrPtr = control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each boot option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gBootOptionCount+1, control);
	if ( tempPtr == NULL )
		return;

	templatePtr = ((UINT8*)ifrPtr + length);
	oneOf = ((UINT8*)tempPtr + length);
  length = UefiGetIfrLength(templatePtr); 

//EIP-48391: Start
	gBootPageHandle = control->ControlHandle;		//++
	for ( i = 0; i < gBootOptionCount; i++ ) {
		flag = (i == value)? (UINT8)HiiGetDefaultMask() : 0;
		//option = HiiAddString( control->ControlHandle, BootGetOptionName( &(gBootData[i]) ) );		// --
		//EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
		if (gLoadOptionHidden && (gBootData [i].Active & LOAD_OPTION_HIDDEN) )
			continue;
		option = GetSpecialBootoptionToken (control->ControlHandle, i);
		MemCopy (oneOf, templatePtr, length);
		// Add one of option
		UefiSetOneOfOption (oneOf, gBootData[i].Option, BOOT_OPTION_SIZE, flag, option);
		oneOf = (UINT8*)oneOf +length;
	}
//EIP-48391: End

  //Create one of option for Disabled
	flag = 0;
	MemCopy (oneOf, templatePtr, length);
	text = HiiGetString (gHiiHandle, STR_CTRL_CHKBOX_DISABLE);
	option = HiiAddString (control->ControlHandle, text);

	//UefiSetOneOfOption (oneOf, 0xFFFF, BOOT_OPTION_SIZE, flag, option); //EIP-97704 BootFFFF
	UefiSetOneOfOption (oneOf, DISABLED_BOOT_OPTION, BOOT_OPTION_SIZE, flag, option);

	MemFreePointer((VOID **)&text);
	oneOf = (UINT8*)oneOf +length;

	// Add an End op to close scope of the One of control
	UefiAddEndOp(oneOf);

	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);

	if(NoVarStoreSupport())
	{
		VOID *ifrPtr;
		UINT16  QuestionId;
		
		control->ControlVariable = VARIABLE_ID_BOOT_ORDER;
		control->ControlConditionalVariable[0] = VARIABLE_ID_BOOT_MANAGER;
		
		ifrPtr = _SpecialGetIfrPtr( control,  VARIABLE_ID_SETUP, NULL);
		QuestionId = UefiGetEqIDQuestionID(ifrPtr);
		QuestionId = QuestionId - GetNoVarStoreBootCountOffset();
		UefiSetEqIDQuestionID(ifrPtr, QuestionId);
	}
}

//EIP70421 & 70422  Support for driver order starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupDriverOrder
//
// Description:	Function to fixup the driver order
//
// Input:		CONTROL_INFO *control,
//				UINT16 value	 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupDriverOrder (CONTROL_INFO *control, UINT16 value)
{
	VOID 	*tempPtr, *ifrPtr;
	VOID 	*templatePtr, *oneOf;
	UINTN 	i;
	CHAR16 	*text;
	UINT8 	length = 0;
	UINT16 	option = 0;
	UINT8 	flag = 0;

	ifrPtr = control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each driver option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gDriverOptionCount+1, control);
	if (NULL == tempPtr)
		return;
	templatePtr = ((UINT8*)ifrPtr + length);
	oneOf = ((UINT8*)tempPtr + length);
	length = UefiGetIfrLength(templatePtr); 
	gDriverPageHandle = control->ControlHandle;
	
	for ( i = 0; i < gDriverOptionCount; i++ )
	{
		flag = (i == value)? (UINT8)HiiGetDefaultMask() : 0;
		if (gLoadOptionHidden && (gDriverData [i].Active & LOAD_OPTION_HIDDEN))
			continue;
		option = _GetSpecialDriveroptionToken (control->ControlHandle, i);
		MemCopy (oneOf, templatePtr, length);
			// Add one of option
		UefiSetOneOfOption (oneOf, gDriverData [i].Option, BOOT_OPTION_SIZE, flag, option);
		oneOf = (UINT8*)oneOf +length;
	}
	//Create one of option for Disabled
	flag = 0;
	MemCopy (oneOf, templatePtr, length);
	text = HiiGetString (gHiiHandle, STR_CTRL_CHKBOX_DISABLE);
	option = HiiAddString (control->ControlHandle, text);

	//UefiSetOneOfOption (oneOf, 0xFFFF, BOOT_OPTION_SIZE, flag, option); //EIP-97704 DriverFFFF
	UefiSetOneOfOption (oneOf, DISABLED_DRIVER_OPTION, BOOT_OPTION_SIZE, flag, option);

	MemFreePointer((VOID **)&text);
	oneOf = (UINT8*)oneOf +length;

	// Add an End op to close scope of the One of control
	UefiAddEndOp(oneOf);

	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}
//EIP70421 & 70422  Support for driver order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBootCondition
//
// Description:	This function updates the Condition to avoid more then one 
//				disabled option in Boot order.
//
// Input:		ControlIndex, Control Info, PrevControlQuestionID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBootCondition (UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID)
{
	// Don't Update the Condition for First option
    if(!ControlIndex)
		return;
	else
	{
        UINT8 u8ChkResult = CheckControlCondition( control );
        if(u8ChkResult == COND_NONE)
        {
    		VARIABLE_INFO *VarInfo;
    		VarInfo = VarGetVariableInfoIndex(control->ControlVariable);
			if(NULL != VarInfo){//EIP-75352 Suppress the warnings from static code analyzer
				UefiCreateDynamicControlCondition(control,(UINT16)VarInfo->VariableID,PrevControlQuestionID,DISABLED_BOOT_OPTION);
			}
        }
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBBSCondition
//
// Description:	This function updates the Condition to avoid more then one 
//				disabled option in BBS Dev order.
//
// Input:		ControlIndex, Control Info, PrevControlQuestionID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBBSCondition(UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID)
{
	// Don't Update the Condition for First option
    if(!ControlIndex)
		return;
	else
	{
        UINT8 u8ChkResult = CheckControlCondition( control );
        if(u8ChkResult == COND_NONE)
        {
    		VARIABLE_INFO *VarInfo;
    		VarInfo = VarGetVariableInfoIndex(control->ControlVariable);
			if(NULL != VarInfo){//EIP-75352 Suppress the warnings from static code analyzer
	    		UefiCreateDynamicControlCondition(control,(UINT16)VarInfo->VariableID,PrevControlQuestionID,DISABLED_BOOT_OPTION);
			}
        }
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBBSOrder
//
// Description:	function to fixup the Legacy Boot device order
//
// Input:		CONTROL_INFO *control,
//				UINT16 value	 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBBSOrder( CONTROL_INFO *control, UINT16 value )
{
	VOID *ifrPtr, *templatePtr, *oneOf, *tempPtr;
	UINTN i;
	UINT16 count,option;
  UINT16 length = 0;
  CHAR16 *text;
	UINT8 flag;

	count = gCurrLegacyBootData->LegacyDevCount;

	ifrPtr = (VOID *)control->ControlPtr;
  length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each device + 1 for Disable option
  tempPtr = UefiCreateOneOfWithOptionsTemplate(count + 1, control);
	if ( tempPtr == NULL )
		return;


	// set real offset into bbs variable for this control. 
  BBSUpdateControlOffset(control);

	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
  length = UefiGetIfrLength(templatePtr);

	for ( i = 0; i < count; i++)
	{
    UINT16 bbsOptionVal = 0;

		MemCopy( oneOf, templatePtr, length );
    flag = (i == value)? (UINT8)HiiGetDefaultMask() : 0;
		option = HiiAddString( control->ControlHandle, BBSGetOptionName( &bbsOptionVal,(UINT16)i ) );
		MemCopy( oneOf, templatePtr, length );
    // Add one of option
    UefiSetOneOfOption(oneOf, bbsOptionVal, BOOT_OPTION_SIZE, flag, option);
    	oneOf = (UINT8*)oneOf +length;
	}

  //Create one of option for Disabled
  flag = 0;
  MemCopy( oneOf, templatePtr, length );
  text = HiiGetString(gHiiHandle,STR_CTRL_CHKBOX_DISABLE);
  option = HiiAddString( control->ControlHandle, text );

	//UefiSetOneOfOption(oneOf, 0xFFFF, BOOT_OPTION_SIZE, flag, option); //EIP-97704 BootFFFF
	UefiSetOneOfOption(oneOf, DISABLED_BOOT_OPTION, BOOT_OPTION_SIZE, flag, option);

  MemFreePointer((VOID **)&text);
 	oneOf = (UINT8*)oneOf +length;

  // Add an End op to close scope of the One of control
  UefiAddEndOp(oneOf);

	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialFixupDelBootOption
//
// Description:	function to fixup the deletion of a boot device option
//
// Input:		CONTROL_INFO *control,
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialFixupDelBootOption (CONTROL_INFO *control)
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i, length = 0;
	
	ifrPtr = (VOID *)control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each boot option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gBootOptionCount + 1, control);
	if ( tempPtr == NULL )
		return;
	
	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
	length = UefiGetIfrLength (templatePtr);
	
	//Copy the first option and skip to next
	MemCopy( oneOf, templatePtr, length );
	oneOf = (UINT8*)oneOf +length;
	
	for ( i = 0; i < gBootOptionCount; i++ )
	{
		if(
			((gBootData[i].DevicePath->Type == BBS_DEVICE_PATH) && (gBootData[i].DevicePath->SubType == BBS_BBS_DP)) ||
			(gLoadOptionHidden && (gBootData [i].Active & LOAD_OPTION_HIDDEN))	
			)
		{
			continue;
		}
		else
		{
			UINT16 option = 0;
			UINT8 flag = 0;
	
			MemCopy( oneOf, templatePtr, length );
			option = HiiAddString (control->ControlHandle, BootGetOptionName (&(gBootData[i])));
			// Add one of option
			UefiSetOneOfOption (oneOf, gBootData[i].Option, BOOT_OPTION_SIZE, flag, option);
			oneOf = (UINT8*)oneOf +length;
		}
	}

	// Add an End op to close scope of the One of control
	UefiAddEndOp (oneOf);
	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField (ifrPtr);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupAddBootOption
//
// Description:	function to fixup the adding of a boot device option
//
// Input:		CONTROL_INFO *control,
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupAddBootOption( CONTROL_INFO *control)
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i,  length = 0;

	ifrPtr = (VOID *)control->ControlPtr;
   	length = UefiGetIfrLength(ifrPtr);
  	//Create one one_of_option for each file sys
	tempPtr = UefiCreateOneOfWithOptionsTemplate( gFsCount, control );
	if ( tempPtr == NULL )
		return;

	UefiUpdateControlVarOffset(control, STRUCT_OFFSET(NEW_BOOT_OPTION, SelFs));

	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
  	length = UefiGetIfrLength(templatePtr);

	for ( i = 0; i < gFsCount; i++)
	{
    UINT16 option = 0;
    UINT8 flag = 0;

    MemCopy( oneOf, templatePtr, length );
    // Add one of option
		option = HiiAddString( control->ControlHandle, gFsList[i].FsId);
    UefiSetOneOfOption(oneOf, (UINT16)i, BOOT_OPTION_SIZE, flag, option);
     	oneOf = (UINT8*)oneOf +length;

	}

  // Add an End op to close scope of the One of control
  UefiAddEndOp(oneOf);
	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}

//EIP70421 & 70422  Support for driver order starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialFixupDelDriverOption
//
// Description:	Function to fixup the deletion of a driver option
//
// Input:		CONTROL_INFO *control,
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialFixupDelDriverOption (CONTROL_INFO *control)
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i, length = 0;

	ifrPtr = (VOID *)control->ControlPtr;
	length = UefiGetIfrLength (ifrPtr);
	//Create one one_of_option for each driver option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gDriverOptionCount + 1, control);
	if (NULL == tempPtr)
		return;
	
	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
	length = UefiGetIfrLength (templatePtr);
	
	//Copy the first option and skip to next
	MemCopy (oneOf, templatePtr, length);
	oneOf = (UINT8*)oneOf +length;
	
	for (i = 0; i < gDriverOptionCount; i++)
	{
		if(
			((gDriverData [i].DevicePath->Type == BBS_DEVICE_PATH) && (gDriverData [i].DevicePath->SubType == BBS_BBS_DP)) ||
			(gLoadOptionHidden && (gDriverData [i].Active & LOAD_OPTION_HIDDEN))	
			)
		{
			continue;
		}
		else
		{
			UINT16 	option = 0;
			UINT8 	flag = 0;
			MemCopy (oneOf, templatePtr, length);
			option = HiiAddString (control->ControlHandle, DriverGetOptionName (&(gDriverData [i])));
			// Add one of option
			UefiSetOneOfOption (oneOf, gDriverData [i].Option, BOOT_OPTION_SIZE, flag, option);
			oneOf = (UINT8*)oneOf +length;
		}
	}
	// Add an End op to close scope of the One of control
	UefiAddEndOp (oneOf);
	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}
//EIP70421 & 70422  Support for driver order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialExplodeControl
//
// Description:	function to explode a perticular contorller
//
// Input:		FRAME_DATA *frame, 
//				CONTROL_INFO *ctrlData, 
//				BOOLEAN *SetFocus
//
// Output:		control Value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT16 _SpecialExplodeControl( FRAME_DATA *frame, CONTROL_INFO *ctrlData, BOOLEAN *SetFocus )
{
	UINT16 value;
	GUID_INFO *guidInfo;

	value = _SpecialGetValue( ctrlData, &guidInfo );
	if ( value == (UINT16)-1 )
		_SpecialAddMultipleControls( frame,ctrlData, guidInfo, SetFocus );

	return value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialControlExtras
//
// Description:	special handling of extra operations
//
// Input:		CONTROL_DATA *ctrlData
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialControlExtras(CONTROL_DATA *ctrlData)
{
	GUID_INFO *guidInfo = NULL;
  UINT16 token = 0;

	UINT16 value = _SpecialGetValue( &ctrlData->ControlData, &guidInfo );
    if ( value != (UINT16)-2 )
	{
		switch(ctrlData->ControlData.ControlType) 
		{
            case CONTROL_TYPE_SUBMENU:// submenu control
				if (guidInfo->GuidKey != GUID_KEY_ADD_BOOT_OPTION)//EIP-79955 To draw GEOMETRICSHAPE_RIGHT_TRIANGLE for AddBootOption
                	((SUBMENU_DATA*)ctrlData)->SubMenuType = 2;
                if (guidInfo->GuidKey == GUID_KEY_BOOT_NOW)
                {
///EIP - 24971
                    token = HiiAddString( ctrlData->ControlData.ControlHandle, BootGetBootNowName(value,gShowAllBbsDev,BootNowInBootOrderSupport()));
///EIP - 24971
                  //Update the submenu prompt field.
                  UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);
                }
		        else if ( guidInfo->GuidKey == GUID_KEY_ERROR_MANAGER )
		        {
			        UINTN size = 0;
                    ERROR_MANAGER *errManager = VarGetNvram( VARIABLE_ID_ERROR_MANAGER, &size );
                    
                    if ( ( errManager != NULL ) && ( value < errManager->ErrorCount ) )
                    {
                        ERROR_LIST *errList = &(errManager->ErrorList[value]);

                        // Update the submenu prompt field.
                        UefiSetPromptField(ctrlData->ControlData.ControlPtr, errList->Summary);
                        ctrlData->ControlData.ControlHelp = errList->DetailInfo;
                        ctrlData->ControlData.ControlHandle = (VOID*)errList->Handle;
                        MemFreePointer( (VOID **)&errManager );
			        }
		        }
                else if (guidInfo->GuidKey == GUID_KEY_DYNAMIC_PAGE)
				{
					UINTN i = 0,j;
					UINTN Index=0;
                    PAGE_INFO *pageInfo;
                    PAGE_INFO *tmppageInfo;
				    PAGE_DATA **page;

                    //EIP 78627: To maintain consistency, show arrow when displaying submenu (SubMenuType=0).  
                    ((SUBMENU_DATA*)ctrlData)->SubMenuType = 0; 

					//Scan for dynamic pages					
					for(i = 0; i < gPages->PageCount; i++)
					{
						pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[i]);
            

						if((pageInfo->PageFlags.PageDynamic == TRUE) && (pageInfo->PageHandle != NULL))
					 	{
							if(Index == value)
							{
								
                                CHAR16 *text;
                                UINT16 Title=0, Help=0 ;
                                
                                // Get Formset Title and Help for Dynamic page
                                GetFormSetTitleAndHelpWrapper (pageInfo->PageHandle, &Title, &Help);
                                
								// Add the Prompt
								text = HiiGetString( pageInfo->PageHandle, pageInfo->PageSubTitle);
		                        token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
                        		UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);
                                                                
                                //EIP# 72333, Display Formset Help for Dynamic page
                                if(Help != 0)
                                {
                                    MemFreePointer( (VOID **)&text );
                                    text = HiiGetString( pageInfo->PageHandle, Help);
		                            token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
                        		    UefiSetHelpField(ctrlData->ControlData.ControlPtr, token);
                                    ctrlData->ControlData.ControlHelp = token ;
                                }//EIP# 72333 End
                            
								// Fix the parent pageID
								ctrlData->ControlData.ControlDestPageID = pageInfo->PageID ;
								pageInfo->PageParentID = gApp->CurrentPage;
                                gDynamicParentPage = gApp->CurrentPage;
                                // Reinitilize the Page.
            					for(j = i; j < gPages->PageCount; j++)
            					{
                                    tmppageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[j]);
                                    if(pageInfo->PageHandle == tmppageInfo->PageHandle )
                                    {
                                        page = &gApp->PageList[tmppageInfo->PageID];
                                        gPage.Destroy( *page, FALSE );
                                        gPage.Initialize( *page, tmppageInfo );
                                    }
                                }
								MemFreePointer( (VOID **)&text );
							}
							Index++;
					    }
					}
					
				}
				else if (guidInfo->GuidKey == GUID_KEY_IDE_SECURITY)
				{             
					CHAR16 *text;
					UINT16 IDEStrToken = TSEIDEPasswordGetName(value);
					

					if(IDEStrToken)
					{
						UINTN size;						
						IDE_SECURITY_CONFIG *ideSecConfig;						
						size = 0;
						//Update mem copy of the IDE sec variable
						ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );					
						if (NULL == ideSecConfig) {
							break;
						}
						TSEIDEUpdateConfig(ideSecConfig, value);
						VarSetValue( VARIABLE_ID_IDE_SECURITY, 0, size, ideSecConfig ); //EIP-83704 to update VARIABLE_ID_IDE_SECURITY variable when HDD is frozen in setup
						MemFreePointer((VOID **)&ideSecConfig);
						
						//VarUpdateVariable (VARIABLE_ID_IDE_SECURITY);
						text = HiiGetString( gHiiHandle, IDEStrToken);
						token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
						//Update the submenu prompt field.
						UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);
						MemFreePointer( (VOID **)&text );
					}
				}
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
		        else if ( guidInfo->GuidKey == GUID_KEY_OEM_CONTROL )
				{
					OEMSpecialGotoFixup(&ctrlData->ControlData,value);
				}
#endif
/**/
                else if (guidInfo->GuidKey == GUID_KEY_BBS_ORDER)
                {
                    CHAR16 *text = NULL;
                    UINTN i,j;
                    BOOT_DATA *bootData;

                    for(i=0,j=0; i<gBootOptionCount; i++)
                    {
                        bootData = &(gBootData[i]);
						 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
						if(gLoadOptionHidden && (bootData->Active & LOAD_OPTION_HIDDEN))
						  continue;
				
                        if ( BBSValidDevicePath(bootData->DevicePath) )
                        {
                            if(value == j)
                            {
                                BBS_BBS_DEVICE_PATH *DevPath = (BBS_BBS_DEVICE_PATH *)bootData->DevicePath;

                                switch(DevPath->DeviceType)
                                {
                                    case BBS_TYPE_FLOPPY:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_FLOPPY_DISK_ORDER));
                                    break;
                                    case BBS_TYPE_HARDDRIVE:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_HARD_DISK_ORDER));
                                    break;
                                    case BBS_TYPE_CDROM:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_CDROM_ORDER));
                                    break;

                                    case BBS_TYPE_PCMCIA:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_PCMCIA_ORDER));
                                    break;

                                    case BBS_TYPE_USB:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_USB_ORDER));
                                    break;

                                    case BBS_TYPE_EMBEDDED_NETWORK:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_NETWORK_ORDER));
                                    break;
                                    case BBS_TYPE_DEV:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_BEV_ORDER));
                                    break;
                                    default:
                                        /// EIP-42520: Updated to get the BBS group type from the Board module in case of a non standard type.
                                        text = HiiGetString( gHiiHandle, BBSGetNonStandardGroupType(DevPath->DeviceType));
                                    break;
                                }

                                token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
                                //Update the submenu prompt field.
                                UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);

                      			MemFreePointer( (VOID **)&text );

                                break;
                            }
                            j++;
                        }
                    }
                }
				else if (GUID_KEY_DRIVER_HEALTH == guidInfo->GuidKey)
				{
					CHAR16	*text;
					((SUBMENU_DATA*)ctrlData)->SubMenuType = 0;		//EIP100099 showing submenu triangle
					text = FindDriverHealthDriverName (value);
					if (NULL != text)
					{
						token = HiiAddString (ctrlData->ControlData.ControlHandle, text);
						UefiSetPromptField (ctrlData->ControlData.ControlPtr, token);
					}
				}
				else if (GUID_KEY_DRV_HEALTH_CTRL_COUNT == guidInfo->GuidKey)
				{
					CHAR16	*text;
					text = GetCtrlNameAndHealth (value);
					if (NULL != text)
					{
						token = HiiAddString (ctrlData->ControlData.ControlHandle, text);
						UefiSetPromptField (ctrlData->ControlData.ControlPtr, token);
					}
				}
				else if (GUID_KEY_DRIVER_HEALTH_ENB == guidInfo->GuidKey)
				{
					((SUBMENU_DATA*)ctrlData)->SubMenuType = 0;				//EIP100099 showing submenu triangle
				}
				break;
			default:
				break;
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialUpdatePageControls
//
// Description:	special fucntion to update the page controls
//
// Input:		UINT32 CurrentPage
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialUpdatePageControls(UINT32 CurrentPage)
{
	PAGE_INFO *thisPage;
    UINT16 i=MAIN_FRAME,j=0, k=0;
	INT16 Value=0;
    CONTROL_INFO *control;
	CONTROL_DATA **ControlData;
	CONTROL_INFO *ControlInfo;
    GUID_INFO *guidInfo;
    FRAME_DATA *fdata;
    BOOLEAN ExitUpdate=FALSE, SetFocus =TRUE;
//Fix EIP:18142	- start
	UINT32			tmpControlCount,tmpCurrentControl,tmpFirstVisibleCtrl;
//Fix EIP:18142	- end

	i = (UINT16) StyleFrameIndexOf(MAIN_FRAME) ;
	thisPage = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[CurrentPage]);
	// find if controls in page need to be exploded 
	// i=0;
    //while(i< thisPage->FrameCount )
	//{
      // for now search main frame only, if needed uncomment code above to do this for all frames in page
			for(j=0;j < thisPage->PageControls.ControlCount;j++)
			{
				control = (CONTROL_INFO*)((UINT8 *)(gControlInfo) + thisPage->PageControls.ControlList[j]);

				switch( _SpecialGetValue( control, &guidInfo ))
				{
				    case (UINT16)-2:
					     break;
				    default:
						// special case, need to reinitialize this frame
						//pdata = (PAGE_DATA*)gApp->PageList[CurrentPage];
						fdata = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[i]; 
						//clist = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[i]->ControlList;
						ControlData = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[i]->ControlList;

//Fix EIP:18142	- Start
						tmpControlCount = fdata->ControlCount;
						tmpCurrentControl = fdata->CurrentControl;
						tmpFirstVisibleCtrl = fdata->FirstVisibleCtrl;
//Fix EIP:18142	- End
	                    for ( k = 0; k < fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->ControlCount; k++, ControlData++ )
                            (*ControlData)->Methods->Destroy( *ControlData, TRUE );
						
                        fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->ControlCount =0;
					    fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->CurrentControl =0;
                        fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->NullCount =0;
						fdata->FirstVisibleCtrl = 0;

					    // loop for al acontrols to either add it "as is" or explode it
	                    for ( k = 0; k < thisPage->PageControls.ControlCount; k++  )
						{
                            ControlInfo = (CONTROL_INFO*)((UINT8 *)gControlInfo + (UINT32)thisPage->PageControls.ControlList[k]);
                            switch(Value=_SpecialExplodeControl(fdata,ControlInfo, &SetFocus))
							{
							case -1:
								break;
							default:
						        if( _SpecialAddControl(fdata,ControlInfo, &SetFocus ) == EFI_SUCCESS)	//EIP-34679: Typo error fix
                                    _SpecialControlExtras((fdata->ControlList[fdata->ControlCount-1])); 
	                           break;
							}

						}
//Fix EIP:18142	- Start
//	To retains the Control Focues in page with has special control
// 	If the control count is different the we will focus to first control as we don't know 
// 	What is added or missing.
						if(fdata->ControlCount == tmpControlCount)
						{
							fdata->CurrentControl=tmpCurrentControl;
							fdata->FirstVisibleCtrl=tmpFirstVisibleCtrl;
							_FrameSetControlFocus( fdata, tmpCurrentControl );
						}
//Fix EIP:18142	- End

						ExitUpdate =TRUE;
					     break;
				}
				if(ExitUpdate)
					break;
			}
    //}
}
//#endif

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
