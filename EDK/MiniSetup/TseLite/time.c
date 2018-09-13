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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/time.c $
//
// $Author: Arunsb $
//
// $Revision: 33 $
//
// $Date: 5/01/14 11:27p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/time.c $
// 
// 33    5/01/14 11:27p Arunsb
// [TAG]  		EIP128948
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	TSE security code check failure for using uninitialized
// variable "Action"
// [RootCause]  	Action variable in TimeHanldeActionKeyMouse and
// _PostPopupEditGetValues is not initialized
// [Solution]  	Initialized Action variable.
// [Files]  		Time.c, TseAdvanced.c
// 
// 32    5/01/14 3:46p Premkumara
// [TAG]  		EIP123727
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Enabling Multiline and in Boot option priorities, Clicking
// on second or third line of the boot item is not selecting boot options
// menu
// [RootCause]  	Proper Condition was not there to check whether Mouse
// Click
// is within the Width and Height of Control or not.
// [Solution]  	Added Proper Condition to check whether Mouse Click
// is within the Width and Height of Control or not.
// [Files]  		Date.c, time.c, frame.c, SubMenu.c, numeric.c,
// PopupString.c, PopupSel.c, ordlistbox.c, PopupPassword.c, UefiAction.c,
// 
// 31    2/11/14 9:03p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 30    11/06/13 1:24a Premkumara
// [TAG]  		EIP128948
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	TSE security code check failure for using uninitialized
// variable "Action"
// [RootCause]  	Action variable in TimeHanldeActionKeyMouse and
// _PostPopupEditGetValues is not initialized
// [Solution]  	Initialized Action variable.
// [Files]  		Time.c, TseAdvanced.c
// 
// 29    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 28    4/05/12 7:26a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 27    2/02/12 1:18p Premkumara
// [TAG]  		EIP75351,75352,75384
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		String.c, boot.c, TseAdvanced.c,Time.c, PopupEdit.c,
// MessageBox.c, Label.c, Edit.c, Date.c
// 
// 26    1/11/12 7:41a Arunsb
// [TAG]  		EIP79965
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Unable to set the date and time with the soft keyboard and
// mouse
// [RootCause]  	Softkbd disabled even the control is active
// [Solution]  	Disabled the softkbd only when control is inactive
// [Files]  		Date.c and time.c
// 
// 25    12/08/11 7:02p Blaines
// [TAG] - EIP 77070 
// [Category]- Function Request
// [Synopsis]- "-"key can not loop the time setting..
// [Files]
// time.c
// 
// 24    12/07/11 9:01a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Moved the UefiPreControlUpdate function call in time.c
// and date.c to the appropriate place.
// [Files]  		time.c, date.c
// 
// 23    11/30/11 12:32a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 22    11/28/11 5:00a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 21    11/21/11 11:02a Premkumara
// [TAG]  		EIP72610
// [Category]  	Improvement
// [Description]  	Moving TSE_MULTILINE_CONTROLS to Binary
// [Files]  		AMITSE-CommonHelper.c, AMITSE.sdl, 
// TSELITE-UefiAction.c, TseLite.sdl, Time.h, Text.c,
// SubMenu.c, ResetButton.c, PopupString.c, PopupSel.h, PopupSel.c, 
// PopupPassword.c, OrderListBox.c, Numeric.c, Label.c, Frame.c, Edit.c, 
// Date.h, Date.c, 
// LEGACY-Legacy.c,
// BOOTONLY- Minisetup.h
// 
// 20    11/20/11 8:20a Rajashakerg
// [TAG]  		EIP62763
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 19    11/19/11 11:49a Arunsb
// EIP 65222 changes has been removed for 2.14 release. Now it is added.
// 
// 18    11/14/11 6:55p Blaines
// [TAG] - EIP 75486 
// [Category]- Function Request
// [Synopsis]- Support grayout condition for readonly controls.
// [Description] - Display readonly controls as grayout, non-selectable.
// [Files]
// AMITSE.sdl, CommonHelper.c, Minisetupext.h, stylecommon.c, Legacy.c,
// date.c, edit.c, label.c, memo.c, menu.c,, numeric.c, ordlistbox.c,
// PopupPassword.c, 
// PopupSel.c, PopupString.c, ResetButton.c, SubMenu.c, Text.c, Time.c,
// UefiAction.c, ctrlcond.c,   
// 
// 17    8/26/11 6:34p Blaines
// [TAG]  		EIP68354
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Callback was invoked during periodic update for time and
// date controls without EFI_IFR_REFRESH_OP.
// [Solution]  	Callback is only invoked for interactive controls.
// [Files]  		TseLite: Time.c, Date.c, 
// Uefi21: Parese.c, Uefi21Wrapper.c
// 
// 16    8/18/11 4:13a Arunsb
// Reverted back to (INT)4.6.2_TSE_2_14_1219 source for making TSE Lite
// release.
// 
// 15    8/02/11 9:49a Arunsb
// EIP 65222 fix uploaded again after the public label
// 4.6.2_TSE_2_14_1219.
// 
// 14    8/01/11 6:07a Arunsb
// Reverted back to (INT)4.6.2_TSE_2_14_1219 source for making public
// label.
// 
// 13    7/28/11 10:36a Blaines
// [TAG] - EIP 65222
// [Category]- Defect 
// [Synopsis]- [ECS-DT][Acer][Q67H2-AM]Adjust RTC time issue.
// [Description]- Set Power On by RTC Alarm -> Time(hh:mm:ss) function
// error. When set 59 at second(ss) column. Press decrease key(-) and the
// second(ss) value can't be modified.
// [Solution] - In Case 2, change "if( (Tm.Second > 0) && (Tm.Hour >
// time->Min ) )" to "if( (Tm.Second > 0) && (Tm.Second > time->Min ) )"
// [Files changed] - Time.c
// [Functions changed] - TimeDecrease
// 
// 12    6/15/11 4:43p Arunsb
// [TAG]           EIP61650 
// [Category]      Bug Fix
// [Severity]      Minor
// [Symptom]       Cannot edit time field when using new "time" format
// [RootCause]     Default refresh interval set to all the time variables
// [Solution]      Default refresh interval provided only for RTC time
// variable
// [Files]         time.c, date.c, parse.c and uefihpktool.exe
// 
// 11    3/09/11 7:23p Madhans
// [TAG]  		EIP48615  
// [Category]  	Improvement
// [Description]  	To support UEFI 2.1 RefreshOp. Based in Refersh Rate
// Controls are refershed periodically.
// [Files]  		minisetupext.h
// SubMenu.h
// SubMenu.c
// Memo.c
// Memo.h
// numeric.c
// numeric.h
// time.c
// Date.c
// PopupSel.c
// PopupSel.h
// PopupString.c
// PopupString.h
// ordlistbox.c
// minisetupext.c
// UefiAction.c
// hii.h
// Uefi20wapper.c
// hiicallback.c
// Parse.c
// tseuefihii.h
// Uefi21wapper.c
// 
// 10    11/30/10 2:07p Blaines
// [TAG] - EIP 48979  
// [Category]- Defect 
// [Severity]- Mordarate
// [Symptom]- Both Date & Time controls of setup menu do not display
// gray-out color when the controls are in the gray-out state.
// 
// [Rootcause] - Improper use of color variable for Date and Time controls
// in the draw function.
// [Solution] - Proper use of color variables to handle normal and
// gray-out state for these controls.
// [Files] - date.c and time.c
// 
// 9     11/17/10 3:08p Madhans
// [TAG] - EIP 48433  
// [Category]- Defect 
// [Severity]- Mordarate
// [Symptom]- While editing Date and Time control pressing
// Pageup/PageDown/Home keys 
// causes to leave Date&Time in the Edit state but changes foucs.
// [Rootcause] - Default case of Action handling not done for Date and
// Time controls.
// [Solution] - Add the Default action handle caes for this controls.
// [Files] - date.c and time.c
// 
// 7     11/10/10 7:02p Blaines
// EIP 47037:  Add range checks to properly edit and update date/time.
// 
// 6     6/04/10 12:53p Blaines
// Add support for UEFI 2.1 date and time controls
// 
// 5     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     2/17/10 7:03p Madhans
// To suppor readonly control
// 
// 4     1/09/10 6:46a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 3     6/23/09 6:53p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 3     6/03/09 11:22a Blaines
// reverting back to alpha labled version
// 
// 1     4/28/09 11:07p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 5     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     3/31/09 4:07p Madhans
// Fix for EDK version
// 
// 3     2/05/09 10:15a Madhans
// Style Module created.
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
// Name:		Time.c
//
// Description:	This file contains code to handle Time control operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

TIME_METHODS gTime =
{
	TimeCreate,
	TimeDestroy,
	TimeInitialize,
	TimeDraw,
	TimeHandleAction,
	TimeSetCallback,
	TimeSetFocus,
	TimeSetPosition,
	TimeSetDimensions,
	TimeSetAttributes,
    TimeGetControlHeight
};

static EFI_TIME EditTime;
CHAR16 TimeTempNum[3];
BOOLEAN CheckKeyinHotKeysList(AMI_EFI_KEY_DATA Key);
VOID _TimeUpdateEntry(TIME_DATA *time);
EFI_STATUS _TimeHandleActionKeyMouse( TIME_DATA *time,  ACTION_DATA *Data);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeDecrease
//
// Description:	to decrease the time, i.e. Hours/Mins/Secs based on the selection
//
// Input:	TIME_DATA *time, UINT16 Selection
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeDecrease(TIME_DATA *time )
{
	EFI_TIME Tm;

	time->ControlActive =TRUE;
	//gRT->GetTime(&Tm,NULL);
	UefiGetTime(&time->ControlData, &Tm);
	

	switch(time->Sel )
	{
		case 0:
			if((Tm.Hour > 0) && (Tm.Hour > time->Min ))
				Tm.Hour--;
			else
				Tm.Hour = /*(time->Max < 23)? (UINT8)time->Max :*/ 23 ; //EIP 77070
			StrZeroPad(Tm.Hour, TimeTempNum); //Update the static time string
			break;
		case 1:
			if( (Tm.Minute > 0) && (Tm.Minute > time->Min ))
				Tm.Minute--;
			else
				Tm.Minute = /*(time->Max < 59)? (UINT8)time->Max :*/ 59; //EIP 77070 
			StrZeroPad(Tm.Minute, TimeTempNum); //Update the static time string
			break;
		case 2:
			if( (Tm.Second > 0) && (Tm.Second > time->Min ) )
				Tm.Second--;
			else
				Tm.Second =  /*(time->Max < 59)? (UINT8)time->Max :*/ 59; //EIP 77070  
			StrZeroPad(Tm.Second, TimeTempNum); //Update the static time string
			break;
	}
	
	UefiSetTime(&time->ControlData, &Tm);
	//gRT->SetTime(&Tm);
	time->ControlActive =FALSE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeIncrease
//
// Description:	to increase the time, i.e. Hours/Mins/Secs based on the selection
//
// Input:	TIME_DATA *time, UINT16 Selection
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeIncrease(TIME_DATA *time )
{
	EFI_TIME Tm;
	time->ControlActive =TRUE;
	//gRT->GetTime(&Tm,NULL);
	UefiGetTime(&time->ControlData, &Tm);

	switch(time->Sel )
	{
		case 0:
			if(Tm.Hour < 23)
				Tm.Hour++;
			else
				Tm.Hour =0;
			StrZeroPad(Tm.Hour, TimeTempNum); //Update the static time string
			break;
		case 1:
			if(Tm.Minute <59)
				Tm.Minute++;
			else
				Tm.Minute =0;
			StrZeroPad(Tm.Minute, TimeTempNum); //Update the static time string
			break;
		case 2:
			if(Tm.Second <59)
				Tm.Second++;
			else
				Tm.Second =0;
			StrZeroPad(Tm.Second, TimeTempNum); //Update the static time string
			break;
	}

	//gRT->SetTime(&Tm);
	UefiSetTime(&time->ControlData, &Tm);
	time->ControlActive =FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeCreate
//
// Description:	this function uses the create function of control
//					and creates and sets the timer
//
// Input:	TIME_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeCreate( TIME_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(TIME_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create(object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gTime;
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the timer
//
// Input:	TIME_DATA *time, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeDestroy( TIME_DATA *time, BOOLEAN freeMem )
{
	if(NULL == time)
	  return EFI_SUCCESS;

	gControl.Destroy( (CONTROL_DATA *)time, FALSE );

	if ( freeMem )
	{
		MemFreePointer((VOID **)&time->EditTime);
		MemFreePointer( (VOID **)&time );
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeInitialize
//
// Description:	this function uses the Initialize function of control
//					and initializes the time
//
// Input:	TIME_DATA *time, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeInitialize( TIME_DATA *time, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( (CONTROL_DATA *)time, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	time->ControlData.ControlHelp = UefiGetHelpField(time->ControlData.ControlPtr);
	time->Interval = (UINT8)time->ControlData.ControlFlags.ControlRefresh;
	time->LabelMargin = (UINT8)gControlLeftMargin;
	time->Sel=0;
	time->ControlFocus=FALSE;
	time->ControlActive = FALSE;
	time->EditTime = EfiLibAllocateZeroPool( sizeof(EFI_TIME) );
	if ( time->EditTime == NULL )
		Status = EFI_OUT_OF_RESOURCES;

	SetControlColorsHook(NULL, NULL, 
						NULL, &(time->FGColor), 
						&(time->SelBGColor), &(time->SelFGColor),
	                    &(time->BGColor), &(time->NSelFGColor), 
						NULL, &(time->LabelFGColor),
						&(time->NSelLabelFGColor),
						NULL, NULL,
						NULL, NULL);


	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeDraw
//
// Description:	function to draw time with attributes
//
// Input:	TIME_DATA *time
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeDraw( TIME_DATA *time )
{
	CHAR16 *t,text[50];
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorTime = time->NSelFGColor ;
	UINT8 ColorLabelTime = (time->ControlFocus)?  time->LabelFGColor : time->NSelLabelFGColor ;
	CHAR16 txt[6];

	if(!(time->ControlActive))
		//Status= gRT->GetTime(&EditTime,NULL);
		UefiGetTime(&time->ControlData, time->EditTime);
		

	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if ( time->ControlData.ControlConditionalPtr != 0x0 )
	//{
		switch( CheckControlCondition( &time->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorTime = ColorLabelTime = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}
	t = HiiGetString( time->ControlData.ControlHandle, UefiGetPromptField(time->ControlData.ControlPtr));
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == t){
		t = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!t)
			return EFI_OUT_OF_RESOURCES;
		EfiStrCpy(t,L" ");
	}
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(time->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( time->Left , time->Top, 
				(UINTN)(time->LabelMargin - time->Left),(UINTN) time->Height,
				t,time->BGColor | ColorLabelTime );
	}
	else
	{
		// boundary overflow  check
		if ( EfiStrLen( t ) > (UINTN)(time->LabelMargin - time->Left  )/*21*/ )
				t[time->LabelMargin - time->Left ] = L'\0';
	
		DrawStringWithAttribute( time->Left , time->Top, (CHAR16*)t, 
				time->BGColor | ColorLabelTime  );
	}
	MemFreePointer((VOID **)&t);

	EfiStrCpy(text,L"[  :  :  ]");
	DrawStringWithAttribute( time->Left + time->LabelMargin, time->Top, (CHAR16*)text, 
			time->BGColor |  ColorTime );

	DrawStringWithAttribute( time->Left +  time->LabelMargin +1 , time->Top, 
			( (time->Sel==0) && (time->ControlActive == TRUE ) ) ? TimeTempNum :StrZeroPad( time->EditTime->Hour,txt), 
			(UINT8)((((time->Sel == 0) && (time->ControlFocus)) ? 
					 time->SelBGColor  | time->SelFGColor : 
					 time->BGColor | ColorTime  )) );

	DrawStringWithAttribute( time->Left +  time->LabelMargin + 4 , time->Top, 
			( (time->Sel==1) && (time->ControlActive == TRUE ) ) ? TimeTempNum :StrZeroPad( time->EditTime->Minute,txt), 
			(UINT8)(  (((time->Sel == 1) && (time->ControlFocus)) ? 
					   time->SelBGColor  | time->SelFGColor :
					   time->BGColor | ColorTime  )) );

	DrawStringWithAttribute( time->Left + time->LabelMargin +7 , time->Top, 
			( (time->Sel==2) && (time->ControlActive == TRUE ) ) ? TimeTempNum :StrZeroPad( time->EditTime->Second,txt), 
			(UINT8)( (((time->Sel == 2) && (time->ControlFocus)) ? 
					  time->SelBGColor  | time->SelFGColor :
					  time->BGColor |  ColorTime  )) );

	FlushLines(time->Top, time->Top);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeHandleAction
//
// Description:	function to handle the actions of time
//
// Input:	TIME_DATA *time, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeHandleAction( TIME_DATA *time, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if(time->ControlActive)
			return Status;

        if (0 == time->ControlData.ControlFlags.ControlRefresh)     //EIP61650 If control not has refresh no need of proceeding
            return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;

		if( --(time->Interval) == 0 )
		{
			// initialize the interval
			time->Interval = (UINT8)(time->ControlData.ControlFlags.ControlRefresh);
            return UefiRefershQuestionValueNvRAM(&(time->ControlData));
		}
		else
			return Status;
	} 

	if ( ! time->ControlFocus )
		return Status;

    if (( Data->Input.Type == ACTION_TYPE_KEY )||(Data->Input.Type == ACTION_TYPE_MOUSE))
        return _TimeHandleActionKeyMouse(time, Data);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeHandleActionKeyMouse
//
// Description:	function to handle the action key of time
//
// Input:	TIME_DATA *time,  ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _TimeHandleActionKeyMouse(TIME_DATA *time, ACTION_DATA *Data)
{
	CONTROL_ACTION Action = ControlActionUnknown;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_TIME Tm;
	AMI_EFI_KEY_DATA key = Data->Input.Data.AmiKey;
    if(time->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;


    //Get time
	//gRT->GetTime( &Tm, NULL );
	UefiGetTime(&time->ControlData, &Tm);
	

    //Get mapping
	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
      Action = MapControlKeysHook(key);
	}
	else if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		{
			//EIP-123727 check whether MouseTop is within the Height and Width of Time Control or not
			if( (Data->Input.Data.MouseInfo.Top >= (UINT32)time->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(time->Top+time->Height)) &&
			  	(Data->Input.Data.MouseInfo.Left >= (UINT32)time->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(time->Left+time->Width))
			)
			{
				Action = ControlActionSelect;		
			}
		}
	}

    switch(Action)
    {
        case ControlActionNextLeft:
//#if !SETUP_STYLE_EZPORT
#if SETUP_STYLE_AWARD
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

			if ( time->Sel == 0 )
				time->Sel = 2;
			else
				time->Sel--;

			Status = EFI_SUCCESS;
        break;
#endif

        case ControlActionNextRight:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

#if SETUP_STYLE_AWARD
			if ( time->Sel == 2 )
				time->Sel = 0;
			else
				time->Sel++;

			Status = EFI_SUCCESS;
#endif
        break;

        case ControlActionNextUp:
        case ControlActionNextDown:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);
        break;

        case ControlActionAbort:
			if ( time->ControlActive )
			{
				time->ControlActive = FALSE;
				Status = EFI_SUCCESS;
            }					
        break;

        case ControlActionSelect:
			if(Data->Input.Type == ACTION_TYPE_MOUSE)
			NumericSoftKbdInit();			
			_TimeUpdateEntry(time);
            _TimeUpdateHelp( time );
// for EZPORT: expressely to go to next entry in time control after hitting enter
//#if ! SETUP_STYLE_EZPORT
#if SETUP_STYLE_AWARD
		break;
#endif
        case ControlActionNextSelection:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

			if ( time->Sel == 2 )
				time->Sel = 0;
			else
				time->Sel++;

			Status = EFI_SUCCESS; 
		break;

        case ControlActionPrevSelection:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

			if ( time->Sel == 0 )
				time->Sel = 2;
			else
				time->Sel--;

			Status = EFI_SUCCESS; 
		break;
        case ControlActionDecreament:
			if(time->ControlActive)
            {
                _TimeUpdateEntry(time);
            }
			_TimeDecrease( time );
			time->ControlActive = TRUE; //Set control state to active, so that control string is updated with the static time string
			Status = EFI_SUCCESS;
        break;

        case ControlActionIncreament:
            if(time->ControlActive)
            {
                _TimeUpdateEntry(time);
            }
			_TimeIncrease( time );
			time->ControlActive = TRUE; //Set control state to active, so that control string is updated with the static time string
			Status = EFI_SUCCESS;
        break;

        case ControlActionNumeric:
			if( !(time->ControlActive))
			{
				time->ControlActive = TRUE;
				switch(time->Sel)
				{
					case 0: //month
						SPrint(TimeTempNum,sizeof(TimeTempNum),L"%d", time->EditTime->Hour);			
						break;
					case 1: // day
						SPrint(TimeTempNum,sizeof(TimeTempNum),L"%d", time->EditTime->Minute);			
						break;
					case 2: //year
						SPrint(TimeTempNum,sizeof(TimeTempNum),L"%d", time->EditTime->Second );			
						break;
				}
			}


			if(EfiStrLen(TimeTempNum)>1)
				TimeTempNum[0] = TimeTempNum[1];

			TimeTempNum[1] = key.Key.UnicodeChar;
			Status = gTime.Draw(time);
        break;
        default:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);
        break;
    }

	if( (((!time->ControlActive)||(!IsMouseClickedonSoftkbd())) && (TSEMouseIgnoreMouseActionHook() == TRUE) )&&
		(((Data->Input.Type == ACTION_TYPE_KEY) &&
		((Action == ControlActionNextLeft) ||(Action == ControlActionNextRight) ||(Action == ControlActionNextUp) ||(Action == ControlActionNextDown) ||(Action == ControlActionPageUp) ||(Action == ControlActionPageDown) ||(Action == ControlActionAbort) ||(Action == ControlActionHome) ||(Action == ControlActionEnd) ||(CheckKeyinHotKeysList(key))) ) ||
		((Data->Input.Type == ACTION_TYPE_MOUSE)&&((!((Data->Input.Data.MouseInfo.Top >= (UINT32)time->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(time->Top+time->Height))&&(Data->Input.Data.MouseInfo.Left >= (UINT32)time->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(time->Left+time->Width))))||(Action == ControlActionAbort))))
		)
	{
		NumericSoftKbdExit();//EIP62763 : Check for softkbd presence and existing the numeric softkbd 
	}
	_TimeUpdateHelp( time );
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetCallback
//
// Description:	Function to set callback.
//
// Input:		TIME_DATA *time, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetCallback( TIME_DATA *time, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetFocus
//
// Description:	Function to set focus.
//
// Input:		TIME_DATA *time, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetFocus(TIME_DATA *time, BOOLEAN focus)
{
	if(focus != FALSE)
	{
		if ( CheckControlCondition( &time->ControlData ) )
			return EFI_UNSUPPORTED;
	}

	if( !(time->ControlFocus && focus) )
	{
		time->ControlFocus = focus;
		// set the selected field to Hour
		time->Sel = 0;
		_TimeUpdateHelp( time );
	}

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetPosition
//
// Description:	Function to set position.
//
// Input:		TIME_DATA *time, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetPosition(TIME_DATA *time, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( time, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetDimensions
//
// Description:	Function to set time dimension.
//
// Input:		TIME_DATA *time, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetDimensions(TIME_DATA *time, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( time, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetAttributes
//
// Description:	Function to set time attributes.
//
// Input:		TIME_DATA *time, UINT8 FGColor, UINT8 BGColor 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetAttributes(TIME_DATA *time, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( time, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeGetControlHeight
//
// Description:	Function to set time height.
//
// Input:		TIME_DATA *time, frame, UINT16 *height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeGetControlHeight(TIME_DATA *time,VOID *frame , UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		*height = 1;	
		Width = (UINT16)(time->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gControlLeftPad));
		text = HiiGetString( time->ControlData.ControlHandle, UefiGetPromptField(time->ControlData.ControlPtr));
	
		newText = StringWrapText( text, Width, height );
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );
	}
	else
	{
		*height = 1;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeUpdateHelp
//
// Description:	function to update the help of time
//
// Input:		TIME_DATA *time
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeUpdateHelp( TIME_DATA *time )
{
	UINT16	helpToken = time->ControlData.ControlHelp;

	switch ( time->Sel )
	{
		case 0:
			UefiGetDateTimeDetails(time->ControlData.ControlPtr,AMI_TIME_HOUR,&helpToken,&time->Min,&time->Max);
			break;

		case 1:
			UefiGetDateTimeDetails(time->ControlData.ControlPtr,AMI_TIME_MIN,&helpToken,&time->Min,&time->Max);
			break;

		case 2:
			UefiGetDateTimeDetails(time->ControlData.ControlPtr,AMI_TIME_SEC,&helpToken,&time->Min,&time->Max);
			break;
		default:
			break;
	}

	time->ControlData.ControlHelp = helpToken;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeUpdateEntry
//
// Description:	function to update the entries in Time
//
// Input:	TIME_DATA *time
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeUpdateEntry(TIME_DATA *time)
{
 EFI_STATUS Status = EFI_SUCCESS;
	if ( time->ControlActive )
	{
		// focus stays on the selection becuase we just edited it
		switch ( time->Sel )
		{
			case 0:
				time->EditTime->Hour = (UINT8)atoi(TimeTempNum, 10);
				break;
			case 1:
				time->EditTime->Minute = (UINT8)atoi(TimeTempNum, 10);
				break;
			case 2:
				time->EditTime->Second = (UINT8)atoi(TimeTempNum, 10);
				break;
			}

		UefiPreControlUpdate(&(time->ControlData));	
		UefiSetTime(&time->ControlData, time->EditTime);
		//For interactive time control invoke the formcallback functions
		if(UefiIsInteractive(&time->ControlData)){//code for callback based on interactive time control
			UINT8 Flags = UefiGetFlagsField(time->ControlData.ControlPtr) ;
			
			
			if(CheckTimeFlags(Flags))
			{
				//for storage type QF_TIME_STORAGE_NORMAL generate time in EFI_HII_TIME format
				
				//Call the callbacks passing the generated input value and value size
				Status = CallFormCallBack(&time->ControlData, UefiGetControlKey(&time->ControlData), 0, AMI_CALLBACK_CONTROL_UPDATE);
			} //else {
				//This case would be handled by UefiSetTime() outside
				//since this case is directly updated using the runtime services
			//}
		}
		//gRT->SetTime( &EditTime ); 
		time->ControlActive = FALSE;
	}
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
