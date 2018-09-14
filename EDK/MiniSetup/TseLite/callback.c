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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/callback.c $
//
// $Author: Arunsb $
//
// $Revision: 39 $
//
// $Date: 5/14/14 11:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/callback.c $
// 
// 39    5/14/14 11:58a Arunsb
// [TAG]	EIP168723
// [Description]	Removed RT attribute for LegacyDevOrder variable.
// [Files]	bbs.c and callback.c
// 
// 38    5/01/14 10:36p Arunsb
// [TAG]  		EIP165284
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System Abnormal when execute Load Default (F9) in BIOS
// Setup
// [RootCause]  	For QF_DATE_STORAGE_TIME and QF_TIME_STORAGE_TIME the
// offset will be 0xFFFF so trying to load default it hung
// [Solution]  	Checked the condition for 0xFFFF
// [Files]  		callback.c
// 
// 37    2/11/14 8:29p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 36    10/07/13 6:40a Premkumara
// Checked-in proper changes
// 
// 35    10/07/13 5:29a Premkumara
// [TAG]  		EIP126466
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BBSOrdre is not saving when Customized SetupMenu is used
// (FixedBootOrder)
// [RootCause]  	gBootData is NULL so causing crashing
// [Solution]  	Checked for NULL and proceed with next BootData instead of
// iterating for next boot data
// [Files]  		TseLite\Callback.c
// 
// 34    10/04/13 4:35p Arunsb
// [TAG]  		EIP136259
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Restore Optimized Defaults doesn't work with IntelRCSetup
// Page on TSE Label 5.004_AmiTse_2_16_1242
// [RootCause]  	Non interactive controls also tried to get the default
// through callback
// [Solution]  	Interactive controls alone tried to get the default
// through callback
// [Files]  		callback.c
// 
// 33    8/06/13 11:27p Arunsb
// [TAG]  		EIP76394
// [Category]  	Improvement
// [Description]  	Support TSE Load/SaveUserDefaults call without
// MesageBox
// [Files]  		callback.c
// 
// 32    7/02/13 10:08a Premkumara
// [TAG]  		EIP120011
// [Category]  	Improvement
// [Description]  	Variable BootOrder and LegacyDevOrder need
// fool-proofing function when TSE load variabled
// [Files]  		Bbs.c, Boot.c, Callback.c, TseLiteHelper.c, Variable.c
// 
// 31    7/02/13 3:49a Premkumara
// [TAG]  		EIP127017
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	On loading optimal defaluts (F3 key) causing setup crash
// [RootCause]  	NULL is not checked properly for gCurrLegacyBootData
// value in LoadDefaults and LoadPreviousValues function
// [Solution]  	Handle NULL check for gCurrLegacyBootData
// [Files]  		Callback.c
// 
// 29    6/10/13 10:48a Arunsb
// Evaluating default in _LoadDefaults supported.
// Callback as manufacturing changed to standard.
// Inconsistent and submitif controls handled properly in _LoadDefaults
// 
// 28    5/22/13 10:58a Premkumara
// [TAG]  		EIP123432 
// [Category]  	Bug Fix
// [Issue Faced]            Take print screen for save & Exit msg box. OK
// of msg box is consumed by Save & Exit msg box.
// 		- Cursor is missing after taking print screen of popupedit box in
// string control
// 		- Printscreen support is not given for Filebrowser feature
// [RootCause]  	- When msg box for Save&Exit is popped and printscreen
// event is called and displaying msg box over Save&Exit. Then msgbox
// handleaction for printscreen event will change the result value in
// _CallbackMsgbox() function so it will break the while loop in
// _CallbackGetValue() function so destroy the next msg box in
// CallbackShowMessageBox() function.
// 		- DrawCursor variable is not set to TRUE after printscreen event
// [Solution]  	- Returning EFI_UNSUPPORTED for printscreen event handling
// function for messgebox and change the result value to 0xff
// 		- Support given for file browser feature
// [Files]  		Callback.c, MessageBox.c, Minisetupext.c, PopupString.c,
// AddBootOption.c
// 		AmiTSEStr.uni, FakeToken.c 
// 
// 27    3/12/13 12:27p Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 26    3/12/13 7:01a Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 25    2/12/13 8:38a Arunsb
// [TAG]  		EIP114800
// [Category]  	Improvement
// [Description]  	_SaveValues without MessageBox. If data param passed as
// NULL then message box wont be displayed.
// [Files]  		TseLite\callback.c
// 
// 24    2/06/13 9:02a Arunsb
// Checked in properly
// 
// 24    1/31/13 12:52p Arunsb
// [TAG]  			EIP109382
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  		Boot Device name incorrect when load default 
// [RootCause]  	Legacy offset in gbootdata corrupted so names displayed
// improperly.
// [Solution]  	Legacy offsets re-calculated properly
// [Files]  		CommonHelper.c, BootOnly\bbs.c and callback.c
// 
// 23    10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 18    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 22    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 20    9/10/12 5:02a Rajashakerg
// [TAG]  		EIP93881 and 93873
// [Category]  	Improvement
// [Description]  	need keep system password after Load default and
// Password saved into NVRAM immediately(not buffer) while it is installed
// in TSE
// [Files]  		frame.c, callback.c, AMITSE.sdl, CommonHelper.c
// 
// 19    5/29/12 4:38a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 18    1/24/12 4:39a Arunsb
// [TAG]  		EIP81581
// [Category]  	Improvement
// [Description]  	Default driver order support
// [Files]  		globals.c, addbootoption.c, callback.c, minisetupext.h and
// variable.c
// 
// 17    1/19/12 10:52a Arunsb
// [TAG]  		EIP79956
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Two boot option entries displayed with the single name
// value
// [RootCause]  	If defaults are loaded then boot order is trying to load
// the improper boot order due to add boot option feature
// [Solution]  	Boot order formed properly for add boot option case.
// If no tsedefaultbootorder module present then gOptimalDefaults
// [VARIABLE_ID_BOOT_ORDER] are saved properly in SaveAddDelBootOptions at
// first time.
// At first time optimal buffer is empty so it was filled with some junk
// value so it is changed to fill the current variable list at first time
// of saving with add boot option feature.
// [Files]  		Addbootoption.c and callback.c
// 
// 16    12/05/11 5:34a Rajashakerg
// [TAG]  		EIP76381 
// [Category]  	Improvement
// [Description]  	Performance: Improving variable data load and usage
// [Files]  		callback.c, minisetupext.c, variable.c, variable.h,
// minisetup.h, Hii.c, FormBrowser2.c
// 
// 15    11/13/11 12:57p Arunsb
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
// 14    8/26/11 8:20a Arunsb
// [TAG]  		EIP65859 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Default bootorder is not loading for loading defautls
// [RootCause]  	Boot device count not updated after restart
// [Solution]  	Boot device count updated after restart too
// [Files]  		callback.c
// 
// 13    6/22/11 9:33a Premkumara
// [TAG]  		EIP57547 
// [Category]  	Improvement
// [Description]  	TSE Feature to Silently Load Defaults, Including Boot
// Order Defaults
// [Files]  		Callback.c
// 
// 12    6/20/11 11:52a Rajashakerg
// [TAG]  		EIP59417   
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE 
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c 
// 
// 11    3/28/11 9:11p Premkumara
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// 
// 
// 
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 10    3/21/11 12:30a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 9     10/05/10 5:38p Madhans
// [TAG] - EIP 45299 
// [Category]- Enhancment
// [Severity]- Minor
// [Symptom]- TSE by default saves the Disbaled BBS devices device path in
// NVRAM Varaiable "DisabledDevs" Variable. In Next boots it depend on
// this variable to consider the device as disabled inaddtion to
// LegacyDevOrder.
// Some BDS customized projects don't want this.
// [Solution]- TSE_SAVE_DISABLED_BBS_DEVICEPATH SDL token created to
// control this option. Bydefault It is Enabled.
// [Files] - callback.c bbs.c commonhelper.c minisetup.h AMITSE.sdl
// 
// 8     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 7     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 6     3/26/10 5:25p Madhans
// EIP 35562: Support To create Boot option in Capital letters.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 10    2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 9     1/09/10 6:30a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 8     12/18/09 2:29p Madhans
// EIP: 32350/32445 To fix the Add/Delete Boot option issues with TSE 2.0.
// To load the boot manager variable when defaults are loaded. 
// 
// 7     10/09/09 10:21a Mallikarjunanv
// updated by removing the PreSystemResetHook, this hook is moved to
// MinisetupExt.c
// 
// 6     10/07/09 11:20a Mallikarjunanv
// Fix to EIP-25987(Load Optimized Defaults(F3) hangs with an empty page):
// Added a condition to check whether the frame has any controls before
// doing any operations on a control.
// 
// 5     9/15/09 9:43a Sudhirv
// updated the support of handling Add Del boot option and added hook
// function call during reset
// 
// 4     8/13/09 7:39a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 3     6/23/09 6:52p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:04p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:07p Madhans
// 2.1 language support.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		callback.c
//
// Description:	This file contains code to handle callbacks
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

ACTION_DATA *gMsgBoxAction;

UINTN _CallbackGetValue( MSGBOX_DATA *msgbox );
VOID _CallbackMsgbox( VOID *container, VOID *object, VOID *cookie );
VOID _LoadDefaults( NVRAM_VARIABLE *defaults, UINTN data );
BOOLEAN _SaveValues( UINTN data );
BOOLEAN LoadDefaultsFromDefaultBuffer( VOID );

extern UINTN gPreviousMsgBox;
extern UINTN gFailsafeMsgBox;
extern UINTN gOptimalMsgBox;
extern UINTN gSaveMsgBox;
extern UINTN gSaveExitMsgBox;
extern UINTN gExitMsgBox;
extern UINTN gSaveResetMsgBox;
extern UINTN gResetMsgBox;
extern UINTN gHelpMsgBox;
extern UINTN gSaveUserMsgBox;
extern UINTN gLoadUserMsgBox;
extern BOOLEAN gBrowserCallbackEnabled;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadPreviousValues
//
// Description:	Callback function for LoadPreviousValue.
//
// Input:		Bool ShowMsgBox.
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadPreviousValues( BOOLEAN showMsgBox )
{
	UINT8 result = MSGBOX_YES;
	UINT16 CurrentBootOption=0;

//- Fix for Screen corruption while editing Date/edit controls.
	FRAME_DATA *MainFrame=NULL;
//-

	if ( showMsgBox )
		result = CallbackShowMessageBox( (UINTN)gPreviousMsgBox, MSGBOX_TYPE_YESNO );

	if ( result == MSGBOX_YES )
	{
		if(gCurrLegacyBootData)
		{
			UINT16 CurLegBootDataValid = 0;
			UINT32 i;

			// Check is gCurrLegacyBootData valid one
		    for (i = 0; i < gBootOptionCount; i++ )
		    {
		        if ( &gBootData[i] == gCurrLegacyBootData )
		            CurLegBootDataValid = 1;
		    }
			// If valid
			if(CurLegBootDataValid)
				CurrentBootOption = gCurrLegacyBootData->Option;
			else
				gCurrLegacyBootData = NULL;
		}

		CleanTempNvramVariableList(); //EIP 76381 : Reset to read the variable from NVRAM
		VarLoadVariables( (VOID **)&gVariableList, NULL );

		// special provisions needed for language
		//VarSetValue( VARIABLE_ID_LANGUAGE, 0, 3, gPrevLanguage );
		VarSetNvram ( VARIABLE_ID_LANGUAGE, gPrevLanguage,gPrevLangSize );

		///Hook to Load previous saved values 
		LoadedPreviousValuesHook();

		PasswordCommitChanges( FALSE );

		TseDiscardAddDelBootOptions();
		TseDiscardAddDelDriverOptions();			//EIP70421 & 70422 Support for driver order
		// reinit the gCurrLegacyBootData
		//if(gCurrLegacyBootData)
		//{
			gCurrLegacyBootData = BootGetBootData(CurrentBootOption);
			if(gCurrLegacyBootData) //EIP-127017 Avoid crashing when press F3 to load previous values
				VarSetValue(VARIABLE_ID_LEGACY_GROUP_INFO, 0, sizeof(UINT16), &(gCurrLegacyBootData->LegacyDevCount));
		//}

		if ( ! gVariableChanged )
			gResetRequired = FALSE;

		UEFICallSetupFormCallBack(AMI_CALLBACK_RETRIEVE);//EIP-53480: Calling the Wraper function with action AMI_CALLBACK_RETRIEVE

		//EIP-126057
		if(gApp!=NULL)
		{
	        //Recreate the special controls to reflect changes
	        gApp->CompleteRedraw = TRUE;

	//- Fix for Screen corruption while editing Date/edit controls.
	        MainFrame = gApp->PageList[gApp->CurrentPage]->FrameList[StyleFrameIndexOf(MAIN_FRAME)];
	        if(MainFrame->ControlCount)
	        if(MainFrame->CurrentControl != FRAME_NONE_FOCUSED)
	            if(MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive == TRUE)
	                MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive = FALSE;
	// -    
		}
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadOptimalDefaults
//
// Description:	Loads the optimal defaults.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadOptimalDefaults( VOID )
{
	///Load optimal defaults modified as a hook
	LoadSetupDefaultsHook( gOptimalDefaults, (UINTN)gOptimalMsgBox );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadFailsafeDefaults
//
// Description:	Loads the failsafe defaults.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadFailsafeDefaults( VOID )
{
	///Load Failsafe defaults modified as a hook
	LoadSetupDefaultsHook( gFailsafeDefaults, (UINTN)gFailsafeMsgBox );
}

BOOLEAN TSEDonotLoadPasswordOnDefaults(VOID);//EIP 93881 & 93873 : Save pwd to nvram and not loading empty pwd on loading defaults.

//EIP 105167 : START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_LoadDefaults
//
// Description:	Loads the defaults with optimal or Failsafe data.
//
// Input:		Bool ShowMsgBox.
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CsmRearrangeBBSOrder (VOID *nvPtr, VOID *DefaultBuffer);
UINT16 EvaluateControlDefault (CONTROL_INFO *CtrlInfo, UINT64 *Defaults);
VOID _LoadDefaults( NVRAM_VARIABLE *defaults, UINTN data )
{
	UINT32 i;
	UINT16 CurrentBootOption=0;
	EFI_STATUS Status;
//- Fix for Screen corruption while editing Date/edit controls.
	FRAME_DATA *MainFrame;
//-

	if ( data == (UINTN)NULL ?1:(CallbackShowMessageBox( data, MSGBOX_TYPE_YESNO ) == MSGBOX_YES) ) //EIP:57547 To avoid draw MessageBox when data is passed as NULL to load Defaults silently
	{
		UINT32	page, control;
		gBrowserCallbackEnabled = TRUE;
		if(gCurrLegacyBootData)
		{
			UINT16 CurLegBootDataValid = 0;

			// Check is gCurrLegacyBootData valid one
		    for ( i = 0; i < gBootOptionCount; i++ )
		    {
		        if ( &gBootData[i] == gCurrLegacyBootData )
		            CurLegBootDataValid = 1;
		    }
			// If valid
			if(CurLegBootDataValid)
				CurrentBootOption = gCurrLegacyBootData->Option;
			else
				gCurrLegacyBootData = NULL;
		}

	

		for ( page = 0; page < gPages->PageCount; page++ )
		{
			PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);
			UINTN Action;
		
			if ( (NULL != pageInfo) && (0 == pageInfo->PageHandle) )
				continue;
		
			for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
			{
				CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);
				
				if( NULL == controlInfo || NULL == controlInfo->ControlPtr)		//Suppressing inconsistent and nosubmit controls so added check for ControlPtr
					continue;	
				
				Status = EFI_SUCCESS;
				if (UefiIsInteractive (controlInfo))
				{
					Action = UefiGetActionWapper (AMI_CALLBACK_FORM_DEFAULT_STANDARD);
					Status = CallFormCallBack (controlInfo, UefiGetControlKey (controlInfo), FALSE, Action);
				}
				if (
						(!UefiIsInteractive (controlInfo) || (EFI_UNSUPPORTED == Status)) &&		//if interactive control returned unsupported then load defaults from buffer
						(!controlInfo->ControlFlags.ControlEvaluateDefault) &&
						(defaults[controlInfo->ControlVariable].Size > 0)
						)
				{
					UINT32 offset = 0, size = 0;
					
					if ((!LoadDefaultsFromDefaultBuffer ()) && (controlInfo->ControlDataWidth ==  0))		//If defaults not present for a control but if the offset present
					{																						//in the variable which has atleast default then
						continue;																			//try to load it if TSE_LOAD_DEFAULTS_FROM_DEFAULTS_BUFFER
					}																						//is enabled.	
					if (CONTROL_TYPE_ORDERED_LIST != controlInfo->ControlType)
					{
						size = UefiGetWidth(controlInfo->ControlPtr);
					}
					else
					{
						size = controlInfo->ControlDataWidth;
					}
					if (0 == size)			//For text and submenu skip loading defaults
					{
						continue;
					}
					offset = UefiGetQuestionOffset(controlInfo->ControlPtr);
					if ((0xFFFF == offset) || ((offset + size) > defaults [controlInfo->ControlVariable].Size))		//QF_DATE_STORAGE_TIME and QF_TIME_STORAGE_TIME offsets will be 0xFFFF so we need to skip it
					{
						continue;
					}
					if ( ( controlInfo->ControlVariable == VARIABLE_ID_LANGUAGE) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_ADD_BOOT_OPTION) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_USER_DEFAULTS) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_IDE_SECURITY) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_LEGACY_DEV_INFO) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_LEGACY_GROUP_INFO) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_ADD_DRIVER_OPTION) ||			//EIP70421 & 70422 Support for driver order
					 (controlInfo->ControlVariable == VARIABLE_ID_DEL_DRIVER_OPTION) ||
					( (TSEDonotLoadPasswordOnDefaults()) && (controlInfo->ControlVariable == VARIABLE_ID_AMITSESETUP && (controlInfo->ControlType == CONTROL_TYPE_PASSWORD) ) ) ) //EIP 93881 & 93873 : Save pwd to nvram and not loading empty pwd on loading defaults.
						continue;
					else if(	((defaults[controlInfo->ControlVariable].Buffer != NULL) && (defaults[controlInfo->ControlVariable].Size))
								&&((VARIABLE_ID_BOOT_ORDER == controlInfo->ControlVariable) || (VARIABLE_ID_DRIVER_ORDER == controlInfo->ControlVariable))
							)
					{
						MemCopy (gVariableList[controlInfo->ControlVariable].Buffer, defaults[controlInfo->ControlVariable].Buffer, defaults[controlInfo->ControlVariable].Size);
						gVariableList[controlInfo->ControlVariable].Size = defaults[controlInfo->ControlVariable].Size;
					}
					else if (VARIABLE_ID_BBS_ORDER == controlInfo->ControlVariable)      //EIP109382: Since boot order loads first legacydevorder corrupted so restructuring with gbootdata 
					{
						if((defaults[controlInfo->ControlVariable].Buffer != NULL) && (defaults[controlInfo->ControlVariable].Size))
							CsmRearrangeBBSOrder (&(gVariableList [controlInfo->ControlVariable]), &(defaults[controlInfo->ControlVariable]));
					}
					else
					{
						if((defaults[controlInfo->ControlVariable].Buffer != NULL) && (defaults[controlInfo->ControlVariable].Size))
							MemCopy (gVariableList [controlInfo->ControlVariable].Buffer + offset, defaults[controlInfo->ControlVariable].Buffer + offset, size);
					}
				}
				if(controlInfo->ControlFlags.ControlEvaluateDefault)
				{
					UINT64 Defaults = 0 ;
					UINT16 size = 0;
					UINT32 offset = 0;
					
					offset = UefiGetQuestionOffset(controlInfo->ControlPtr);

					//EIP: 57402 Evaluating the Control Default
					size = EvaluateControlDefault(controlInfo,&Defaults);
					 VarSetValue(controlInfo->ControlVariable, offset, size, &Defaults );
					// EIP: 57402 Setiing the Evaluated value to the gOptimalDefaults
					//if(DefaultId == EFI_HII_DEFAULT_CLASS_MANUFACTURING)
						_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, offset, size, &Defaults );
				}
			}
		}
		
		gBrowserCallbackEnabled = FALSE;
		PasswordCommitChanges( FALSE );

		TseDiscardAddDelBootOptions();
		TseDiscardAddDelDriverOptions();							//EIP70421 & 70422 Support for driver order

		// reinit the gCurrLegacyBootData
//		if(gCurrLegacyBootData)                 //(EIP61172) If defaults is loaded, boot order defaults is not loading after a restart. So commented.
//		{                                       //(EIP61172)
			gCurrLegacyBootData = BootGetBootData(CurrentBootOption);
			if(gCurrLegacyBootData) //EIP-127017 Avoid crashing when press F3 to load defaults
				VarSetValue(VARIABLE_ID_LEGACY_GROUP_INFO, 0, sizeof(UINT16), &(gCurrLegacyBootData->LegacyDevCount));
//		}                                       //(EIP61172)

		gResetRequired = TRUE;

        LoadedConfigDefaultsHook();
        
        //EIP-126057
        if(gApp!=NULL)
        {
            //Recreate the special controls to reflect changes
              gApp->CompleteRedraw = TRUE;

      //- Fix for Screen corruption while editing Date/edit controls.
              MainFrame = gApp->PageList[gApp->CurrentPage]->FrameList[StyleFrameIndexOf(MAIN_FRAME)];

          //EIP-25987: Load Optimized Defaults(F3)hangs in a empty page || Fix: Check whether the frame has any controls before doing any operation on a control. 
          if(MainFrame->ControlCount)
              if(MainFrame->CurrentControl != FRAME_NONE_FOCUSED)
                  if(MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive == TRUE)
                      MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive = FALSE;
      // -      
        }
	}
}
//EIP 105167 : END
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveAndExit
//
// Description:	Function to save and exit
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SaveAndExit( VOID )
{
	if ( _SaveValues( (UINTN)gSaveExitMsgBox ) )
	{
		gVariableChanged = TRUE;
		return TRUE;
	}

	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveWithoutExit
//
// Description:	Function to save without exit
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveWithoutExit( VOID )
{
	if ( _SaveValues( (UINTN)gSaveMsgBox ) )
		gVariableChanged = TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveAndReset
//
// Description:	Function to save and reset
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SaveAndReset( VOID )
{
	if ( _SaveValues( (UINTN)gSaveResetMsgBox ) )
	{
		gVariableChanged = TRUE;
        gResetRequired = TRUE;
		return TRUE;
	}

	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetSys
//
// Description:	Function to reset
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ResetSys( VOID )
{
	if ( CallbackShowMessageBox( (UINTN)gResetMsgBox, MSGBOX_TYPE_YESNO ) == MSGBOX_YES )
	{
        	gResetRequired = TRUE; // force a reset 
		gVariableChanged = FALSE;
		return TRUE;
	}

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SaveValues
//
// Description:	Function to save the given values
//
// Input:	UINTN data
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _SaveValues( UINTN data )
{
	UINT32 i;
	NVRAM_VARIABLE *nvPtr;
	EFI_GUID AmitseNvramUpdateGuid = AMITSE_NVRAM_UPDATE_GUID;
	EFI_GUID AmitseBootOrderChangeGuid = AMITSE_BOOT_ORDER_CHANGE_GUID;

	if (data == (UINTN)NULL ? 1 : (CallbackShowMessageBox (data, MSGBOX_TYPE_YESNO) == MSGBOX_YES) ) //To avoid draw MessageBox when data is passed as NULL to save data silently EIP114800
	{
		//Check for NO_SUBMIT_IF before saving data in every page
		if(CheckNoSubmitIf())
		{
			return FALSE; //cant save Invalid Submit value
		}
		//EIP-126057
		if(gApp!=NULL)
		{
	        //Check for inconsistency before saving data
	        if(CheckInconsistence((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[gApp->CurrentPage])))
	        {
	            return FALSE; //cant save inconsistent value
	        }
		}

		if(gResetRequired)
		{	//Let's update the SaveState Variable 
			UINT32 SaveStateVarNum;
			UINT16 SaveState=SETUP_SAVED_AND_RESET_REQUIRED;
			if(VarGetVariableInfoId( SETUP_SAVE_STATE_INFO_KEY_ID, &SaveStateVarNum ))
				VarSetValue(SaveStateVarNum,0,sizeof(UINT16),&SaveState);
		}

		nvPtr = gVariableList;
		for ( i = 0; i < gVariables->VariableCount; i++, nvPtr++ )
		{
			if(VARIABLE_ID_BOOT_ORDER == i)
			{
                UINTN j,k=0,n=0, CurrSize = 0;
                UINT16 *BootOrder = NULL, *CurrOrder = NULL;
                BOOT_DATA *pBootData = NULL;

				TseSaveAddDelBootOptions();

                BootOrder = EfiLibAllocateZeroPool(nvPtr->Size);
                MemCopy(BootOrder,nvPtr->Buffer,nvPtr->Size);

                //Disable all options
                for(j=0;j<gBootOptionCount;j++)
				{
					if (!(gBootData[j].Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden
					{	
	                    gBootData[j].Active &= ~(LOAD_OPTION_ACTIVE);
					}
				}
                //Enable options in BootOrder
                for(j=0;j<gBootOptionCount;j++)
                {
                    pBootData = BootGetBootData(BootOrder[j]);
                    if(pBootData)
					{
						if (!(pBootData->Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden	
						{
	                        pBootData->Active |= LOAD_OPTION_ACTIVE;
						}
					}
                }

                //Save boot options
                for(j=0;j<gBootOptionCount;j++)
                {
                    CHAR16 varName[] = L"BootXXXX";
                    BOOT_OPTION *pOption;
                    UINTN OptionSize;

                    OptionSize = 0; pOption = NULL;
                    SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1),gBootFormarSpecifier, gBootData[j].Option );
                    pOption = (BOOT_OPTION *)VarGetNvramName( varName, &gEfiGlobalVariableGuid, NULL, &OptionSize );

                    pOption->Active = gBootData[j].Active;

                    VarSetNvramName(varName,
                        &gEfiGlobalVariableGuid,
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        pOption,
                        OptionSize);
                    
                    MemFreePointer((VOID **)&pOption);
                }
				n=0;
                //Enabled options first
                for(k=0;k<gBootOptionCount;k++)
                {
                    if(DISABLED_BOOT_OPTION == BootOrder[k])
				    {	
			//add Disabled options
	                	for(j=n; j < gBootOptionCount; j++ )
	                	{
	                    		if ( (!(gBootData[j].Active & LOAD_OPTION_ACTIVE)) && (!(gBootData[j].Active & LOAD_OPTION_HIDDEN)) )
	                    		{
									BootOrder[k] = gBootData[j].Option;
									n=j;
									n++;
									break;
	                       		}
	                	}
				    }		
                        
                }

                ASSERT(k==gBootOptionCount);

                //Signal TPM if Boot order has changed
				CurrOrder = VarGetNvramName(L"BootOrder", &gEfiGlobalVariableGuid, NULL, &CurrSize);

                if( CurrSize != (k*sizeof(UINT16)) )
                    EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                else if(CurrOrder)
                {
                    if (MemCmp((UINT8 *)CurrOrder, (UINT8 *)BootOrder, CurrSize))
						EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                }

                MemFreePointer((VOID **)&CurrOrder);

                //Save boot order
                VarSetNvramName(L"BootOrder",
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    BootOrder,
                    k * sizeof(UINT16));

                MemFreePointer((VOID **) &BootOrder);

                //Continue to next variable
                continue;
			}
			//EIP70421 & 70422  Support for driver order starts
			if(VARIABLE_ID_DRIVER_ORDER == i)
			{
                UINTN 	j, k=0, n=0;
                UINT16 	*DriverOrder = NULL;
                BOOT_DATA *pDriverData = NULL;

				TseSaveAddDelDriverOptions ();

                DriverOrder = EfiLibAllocateZeroPool (nvPtr->Size);
                MemCopy (DriverOrder,nvPtr->Buffer,nvPtr->Size);

                //Disable all options
                for (j = 0; j < gDriverOptionCount; j ++)
				{
					if (!(gDriverData [j].Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden
					{
                    	gDriverData [j].Active &= ~(LOAD_OPTION_ACTIVE);
					}
				}
                //Enable options in DriverOrder
                for (j = 0; j < gDriverOptionCount; j ++)
                {
                    pDriverData = DriverGetDriverData (DriverOrder [j]);
                    if(pDriverData)
					{
						if (!(pDriverData->Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden
						{	
	                        pDriverData->Active |= LOAD_OPTION_ACTIVE;
						}
					}
                }
                //Save driver options
                for (j  = 0; j < gDriverOptionCount; j ++)
                {
                    CHAR16 varName[] = L"DriverXXXX";
                    BOOT_OPTION *pOption;
                    UINTN OptionSize;

                    OptionSize = 0; pOption = NULL;
                    SPrint (varName, sizeof (CHAR16) * (EfiStrLen (varName) + 1), gDriverFormarSpecifier, gDriverData [j].Option );
                    pOption = (BOOT_OPTION *)VarGetNvramName (varName, &gEfiGlobalVariableGuid, NULL, &OptionSize );

                    pOption->Active = gDriverData [j].Active;

                    VarSetNvramName (varName,
                        &gEfiGlobalVariableGuid,
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        pOption,
                        OptionSize);
                    
                    MemFreePointer((VOID **)&pOption);
                }
				n=0;
                //Enabled options first
                for (k = 0; k < gDriverOptionCount; k ++)
                {
                    if(DISABLED_BOOT_OPTION == DriverOrder [k])
				    {	
			//add Disabled options
	                	for (j = n; j < gDriverOptionCount; j++ )
	                	{
                    		if ( (!(gDriverData [j].Active & LOAD_OPTION_ACTIVE)) && (!(gDriverData [j].Active & LOAD_OPTION_HIDDEN)) )
                    		{
								DriverOrder [k] = gDriverData [j].Option;
								n = j;
								n ++;
								break;
                       		}
	                	}
				    }		
                        
                }

                ASSERT (k == gDriverOptionCount);

                //Signal TPM if Boot order has changed			//No need of signalling the event for driver order change
/*				CurrOrder = VarGetNvramName (L"DriverOrder", &gEfiGlobalVariableGuid, NULL, &CurrSize);

                if (CurrSize != (k*sizeof(UINT16)))
                    EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                else if (CurrOrder)
                {
                    if (MemCmp ((UINT8 *)CurrOrder, (UINT8 *)DriverOrder, CurrSize) )
						EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                }

                MemFreePointer((VOID **)&CurrOrder);*/

                //Save boot order
                VarSetNvramName(L"DriverOrder",
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    DriverOrder,
                    k * sizeof(UINT16));

                MemFreePointer((VOID **) &DriverOrder);

                //Continue to next variable
                continue;
			}
			//EIP70421 & 70422  Support for driver order ends

			if(VARIABLE_ID_BBS_ORDER == i)
			{
				CsmSaveBBSOrder(nvPtr);
                //Continue to Next variable
                continue;
			}

			VarSetNvram( i, nvPtr->Buffer, nvPtr->Size );
		}

		PasswordCommitChanges( TRUE );

		TSESetHDDPassword();

        SavedConfigChangesHook();

		EfiLibNamedEventSignal (&AmitseNvramUpdateGuid);

		return TRUE;
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveBBSOrder
//
// Description:	Function to save the bbs device order
//
// Input:	NVRAM_VARIABLE *nvPtr
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveBBSOrder(NVRAM_VARIABLE *nvPtr)
{
    UINT16 *BootOrder;
    UINTN BootOrderSize,p;
    BBS_ORDER_TABLE *NewLegacyOrder, *NewDevEntry, *BufferDevEntry;
    UINT8 *NewBuffer, *NewBuffEntry;
    BOOT_DATA *pBootData;
    BBS_ORDER_LIST *BBSList = NULL;
    UINT16 count,r,s;
    UINT8 *CurrOrder = NULL;
    UINTN CurrSize = 0;
    UINTN DPSize = 0;                
    VOID *DisDPs = NULL;
    EFI_GUID BootManGuid = BOOT_MANAGER_GUID;
    EFI_GUID AmitseBootOrderChangeGuid = AMITSE_BOOT_ORDER_CHANGE_GUID;
    UINT32 LegDevOrderAttribute = 7;

    BootOrderSize = 0;
    BootOrder = VarGetNvramName(L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize);

    if (0 == BootOrderSize)
        return; //continue;

    NewLegacyOrder = EfiLibAllocateZeroPool(nvPtr->Size);
    NewBuffer = EfiLibAllocateZeroPool(nvPtr->Size);

    //NOTE: Taking advantage of the fact that
    //VARIABLE_ID_BBS_ORDER is after
    //VARIABLE_ID_BOOT_ORDER
    NewDevEntry = NewLegacyOrder;
    NewBuffEntry = NewBuffer;
    for(p=0; p<(BootOrderSize/sizeof(UINT16)); p++)
    {
        pBootData = BootGetBootData(BootOrder[p]);
		//EIP:59417 - Error Handling in case of pBootData is NULL. If its NULL the setupgets a CRASH
		if(pBootData == NULL)
		 goto DONE;

        if(BBSValidDevicePath(pBootData->DevicePath))
        {
            BufferDevEntry = (BBS_ORDER_TABLE *)(nvPtr->Buffer + pBootData->LegacyEntryOffset);

				if ( (BufferDevEntry->Length >= nvPtr->Size) || (0 == BufferDevEntry->Length) ) //EIP-120011
				{
					goto DONE;
				}

            BBSList = pBootData->OrderList;

            count = pBootData->LegacyDevCount;

            MemCopy(NewDevEntry, BufferDevEntry, sizeof(UINT32)+(count+1)*sizeof(UINT16));
            MemCopy(NewBuffEntry, BufferDevEntry, sizeof(UINT32)+(count+1)*sizeof(UINT16));
        
	        //----------------------------------------------------------------------------------//       
	        // EIP-35863: This block considers the case of legacy devices being positioned	//
	        // anywhere in the LegacyDevOrder (whether enabled or disabled)			//
	        //----------------------------------------------------------------------------------// 
	        if(count>0) //Disabled boot options exist
            {
                for(r=0;r<count;r++)
                {
      		        //See if a given index in BBSList exist in TypeEntry              
		            for(s=0;s<count;s++)
                    {
                        if(BBSList[r].Index == NewDevEntry->Data[s])
			            {
    				        break;
			            }
                    }

		            if(s>=count) //Index Not present
                    {
			            //Find the first disabled slot
			            for(s=0;s<count;s++)
              		    {
                      	    if(NewDevEntry->Data[s] == DISABLED_BOOT_OPTION)
			                {
				                //Add device path to Nvram variable
                                if(gIsSaveDisabledBBSDevicePath)
                  			        CsmBBSSetDisabled(BBSList[r].Index, &DisDPs, &DPSize);
				                NewDevEntry->Data[s] = BBSList[r].Index;
               			        NewDevEntry->Data[s] |= BBS_ORDER_DISABLE_MASK;
				                break;
			                }
               		    }
                    }
                }
            }

            pBootData->LegacyEntryOffset = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;

            NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + sizeof(UINT32)+(count+1)*sizeof(UINT16));
            NewBuffEntry = NewBuffEntry + sizeof(UINT32)+(count+1)*sizeof(UINT16);
        }
    }

DONE:
    //Update the nv buffer with the re ordered list
    MemFreePointer((VOID **) &(nvPtr->Buffer));
    nvPtr->Buffer = NewBuffer;

    //Signal TPM if BBS order has changed
	CurrOrder = VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, &LegDevOrderAttribute, &CurrSize );

	if(CurrOrder)
	{
		if(MemCmp((UINT8 *)CurrOrder, (UINT8 *)NewLegacyOrder, CurrSize))
			EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);

		MemFreePointer((VOID **) &CurrOrder);
	}

    //Save BBS order
    VarSetNvramName(L"LegacyDevOrder",
        &gLegacyDevGuid,
        LegDevOrderAttribute,
        NewLegacyOrder,
        nvPtr->Size);

    if(gIsSaveDisabledBBSDevicePath)
    {
        //Save disabled device paths
        VarSetNvramName(L"DisabledDevs",
            &BootManGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
            DisDPs,
            DPSize);
    
        MemFreePointer((VOID **) &DisDPs);
        MemFreePointer((VOID **) &BootOrder);
    }
    MemFreePointer((VOID **) &NewLegacyOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ExitApplication
//
// Description:	Function to exit form the setup application
//
// Input:	None
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ExitApplication( VOID )
{
	if ( CallbackShowMessageBox( (UINTN)gExitMsgBox, MSGBOX_TYPE_YESNO ) == MSGBOX_YES )
	{
		if ( ! gVariableChanged )
			gResetRequired = FALSE;

		LoadPreviousValues( FALSE );
		gVariableChanged = FALSE;
		return TRUE;
	}

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowHelpMessageBox
//
// Description:	Function to Display the help message box
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ShowHelpMessageBox( VOID )
{
	CallbackShowMessageBox( (UINTN)gHelpMsgBox, MSGBOX_TYPE_OK | MSGBOX_STYLE_LEFT );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CallbackShowMessageBox
//
// Description:	Callback function to Display the message box
//
// Input		:	UINTN data, 
//					UINT8 type
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CallbackShowMessageBox( UINTN data, UINT8 type )
{
	EFI_STATUS Status;
	UINT8 retValue = (UINT8)-1;
	MSGBOX_DATA *msgbox = NULL;

	CONTROL_INFO dummy;

	Status = gMsgBox.Create( &msgbox );
	if ( EFI_ERROR( Status ) )
		return retValue;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
	dummy.ControlPtr = (VOID*)data;
	dummy.ControlFlags.ControlVisible = TRUE;

	Status = gMsgBox.Initialize( msgbox, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

	gMsgBox.SetType( msgbox, type );
	retValue = (UINT8)_CallbackGetValue( msgbox );

Done:
	gMsgBox.Destroy( msgbox, TRUE );

	return retValue;
}

static UINT8 result = (UINT8)-1;
static CALLBACK_MESSAGEBOX  gCbMsgBox = { { CALLBACK_TYPE_MESSAGEBOX, sizeof(CALLBACK_MESSAGEBOX) }, 0 }; 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_CallbackGetValue
//
// Description:	Callback function to get the message box return value
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	Message box return value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _CallbackGetValue( MSGBOX_DATA *msgbox )
{
	ACTION_DATA *action = gMsgBoxAction;
	EFI_STATUS Status = EFI_SUCCESS;
	result = (UINT8)-1;
	gMsgBox.SetCallback( msgbox, NULL, _CallbackMsgbox, &gCbMsgBox );

	while ( result == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		gMsgBox.Draw( msgbox );

		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;

		Status = gMsgBox.HandleAction( msgbox, action );

		if (EFI_ERROR(Status))//EIP-123432
			result = 0xff;

		DoRealFlushLines();
	}

	return result;
}

VOID _CallbackMsgbox( VOID *container, VOID *object, VOID *cookie )
{
	if ( (cookie != NULL) && ( ((CALLBACK_MESSAGEBOX*)cookie)->Header.Type == CALLBACK_TYPE_MESSAGEBOX) )
		result = (UINT8)(((CALLBACK_MESSAGEBOX*)cookie)->Result);
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
