//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Date.c $
//
// $Author: Premkumara $
//
// $Revision: 32 $
//
// $Date: 5/01/14 3:39p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Date.c $
// 
// 32    5/01/14 3:39p Premkumara
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
// 31    11/20/12 12:41a Arunsb
// [TAG]  		EIP107049
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If set Token "STYLE_DATE_FORMAT" to change the date display
// type to [yyyy/mm/dd], it can't key-in correct value to set the date
// value, only use the +/- command to set the date value
// [Files]  		Date.c
// 
// 30    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 29    4/05/12 7:13a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 28    2/02/12 1:16p Premkumara
// [TAG]  		EIP75351,75352,75384
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		String.c, boot.c, TseAdvanced.c,Time.c, PopupEdit.c,
// MessageBox.c, Label.c, Edit.c, Date.c
// 
// 27    1/18/12 7:27a Rajashakerg
// [TAG]  		EIPEIP 79487:
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Decreasing YEAR field displayed yearr with XX before 2005
// and after 2098.
// [RootCause]  	Improper handling of the date and year field of the date 
// control.
// [Solution]  	Global variable DateTempNum is handled properly while
// updating the date and year field of the date control.
// [Files]  		Date.c
// 
// 26    1/18/12 6:22a Rajashakerg
// [TAG]  		EIP79961 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	"Non RTC date control - decreasing from year value 0001
// displayed 65535 without closing bracket.
// [RootCause]  	In date draw function we are providing only 4 digits for
// year. But Tm.year value when decremented after least value its drawing
// the 65535 which is the maximum.
// [Solution]  	Restricted maximum value for year to 9999 such that it
// wont erase the ']' when incremented over 9999.
// When incremented over 9999 provided 0 to it. 
// [Files]  		Date.c
// 
// 25    1/11/12 7:42a Arunsb
// [TAG]  		EIP79965
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  		Unable to set the date and time with the soft keyboard and
// mouse
// [RootCause]  	Softkbd disabled even the control is active
// [Solution]  	Disabled the softkbd only when control is inactive
// [Files]  		Date.c and time.c
// 
// 24    1/05/12 1:10p Blaines
// [TAG]  		EIP 80092
// [Category]  	Defect
// [Symptom]  	Day of week is not properly calculated for 2012 in Setup
// [RootCause]  	Local variables are declared type UINT.		
// [Solution]	Change the local variable type from UINT to INTN.
// 
// [Files Changed]
// - date.c
// 
// [Functions Changed]
// - _DateGetWeekDay
// 
// 23    12/07/11 9:02a Rajashakerg
// TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Moved the UefiPreControlUpdate function call in time.c
// and date.c to the appropriate place.
// [Files]  		time.c, date.c
// 
// 22    11/30/11 11:51p Rajashakerg
// 
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 21    11/30/11 12:49a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 20    11/28/11 4:55a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 19    11/28/11 2:02a Premkumara
// [TAG]  		EIP75384 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		UefiWapper.c, Hii.c, Expression.c, CtrlCond.c, PopupSel.c,
// Minisetupext.c, Menu.c, Date.c, Ezport\Stylecommon.c,
// EzportPlus\StyleCommon.c,
// 
// 18    11/21/11 12:12p Premkumara
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
// 17    11/20/11 7:44a Rajashakerg
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
// 16    11/14/11 6:55p Blaines
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
// 15    8/26/11 6:34p Blaines
// [TAG]  		EIP68354
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Callback was invoked during periodic update for time and
// date controls without EFI_IFR_REFRESH_OP.
// [Solution]  	Callback is only invoked for interactive controls.
// [Files]  		TseLite: Time.c, Date.c, 
// Uefi21: Parese.c, Uefi21Wrapper.c
// 
// 14    6/15/11 4:46p Arunsb
// [TAG]           EIP61650 
// [Category]      Bug Fix
// [Severity]      Minor
// [Symptom]       Cannot edit time field when using new "time" format
// [RootCause]     Default refresh interval set to all the time variables
// [Solution]      Control refreshed only if refresh flag set.
// [Files]         time.c, date.c, parse.c and uefihpktool.exe
// 
// 13    3/09/11 7:23p Madhans
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
// 12    12/02/10 2:34p Madhans
// [TAG] - EIP 48169  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Code Cleanup and Compiler Warning need to resolved.
// [Rootcause] Warnings reported when we build AMI higher Warning level.
// [Solution]- 1. Fix the warnings and do the code cleanup. 
//             2. Introduce proper checks.
//             3. change the popupSel.c to not change the Option/variable
// cache to default or first option
//                when the variable cache is not matching with any of
// option.
// [Files] - commonoem.c bbs.c boot.c hiistring.c resource.c
// popuppassword.c popupsel.c
//           expression.c hii.c parse.c
// 
// 11    11/30/10 2:07p Blaines
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
// 10    11/17/10 3:09p Madhans
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
// 8     11/10/10 6:59p Blaines
// Fix issue with date control not calling the proper uefi2.1 funtion to
// set date.
// 
// 7     6/04/10 12:53p Blaines
// Add support for UEFI 2.1 date and time controls
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 7     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 6     2/17/10 7:03p Madhans
// To suppor readonly control
// 
// 5     1/09/10 6:48a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/18/09 6:35p Blaines
// Support additional date styles
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
// 2     5/20/09 3:42p Blaines
// Update support for date format
// 
// 1     4/28/09 11:04p Madhans
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
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Date.c
//
// Description:	This file contains code to handle Date control operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


DATE_METHODS gDate =
{
	DateCreate,
	DateDestroy,
	DateInitialize,
	DateDraw,
	DateHandleAction,
	DateSetCallback,
	DateSetFocus,
	DateSetPosition,
	DateSetDimensions,
	DateSetAttributes,
    DateGetControlHeight

};
BOOLEAN CheckKeyinHotKeysList(AMI_EFI_KEY_DATA Key);
VOID _DateUpdateEntry(DATE_DATA *time);
EFI_STATUS _DateHandleActionKeyMouse(DATE_DATA *date,  ACTION_DATA *Data);
UINT16 DayNames[] =
{
	STRING_TOKEN(STR_DAY_SUNDAY),
	STRING_TOKEN(STR_DAY_MONDAY),
	STRING_TOKEN(STR_DAY_TUESDAY),
	STRING_TOKEN(STR_DAY_WEDNESDAY),
	STRING_TOKEN(STR_DAY_THURSDAY),
	STRING_TOKEN(STR_DAY_FRIDAY),
	STRING_TOKEN(STR_DAY_SATURDAY),
};

CHAR16 DateTempNum[5];

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateCreate
//
// Description:	Function to create the date, which uses the Control fucntions.
//
// Input:	DATE_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateCreate( DATE_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(DATE_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gDate;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateDestroy
//
// Description:	Function to destroy the date, which uses the Control fucntions.
//
// Input:	DATE_DATA *date, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateDestroy( DATE_DATA *date, BOOLEAN freeMem )
{
	if(NULL == date)
	  return EFI_SUCCESS;

	gControl.Destroy( date, FALSE );

	if ( freeMem )
		MemFreePointer( (VOID **)&date );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateInitialize
//
// Description:	Function to initialize the date, which uses the Control fucntions.
//
// Input:	DATE_DATA *date, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateInitialize( DATE_DATA *date, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( date, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	date->ControlData.ControlHelp = UefiGetHelpField(date->ControlData.ControlPtr);
	date->Interval = (UINT8)date->ControlData.ControlFlags.ControlRefresh;
	date->LabelMargin = (UINT8)gControlLeftMargin;
	date->Sel = 0;
	date->ControlFocus = FALSE;
	date->ControlActive = FALSE;

	SetControlColorsHook(NULL, NULL,
						NULL, &(date->FGColor), 
						&(date->SelBGColor), &(date->SelFGColor),
						&(date->BGColor), &(date->NSelFGColor),
						NULL, &(date->LabelFGColor),
						&(date->NSelLabelFGColor),
						NULL, NULL,
						NULL, NULL );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateInitialize
//
// Description:	Function to draw the date.
//
// Input:	DATE_DATA *date
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateDraw( DATE_DATA *date )
{
	CHAR16 *t,text[50],txt[5];
	UINTN day;
	EFI_TIME Tm;
	UINTN nIndex,nDateLen,nEFIDateLen,i = 0;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorDate = date->NSelFGColor /*date->FGColor*/ , NScolor,SColor;
	UINT16 MarginLeft = date->Left + date->LabelMargin;
	UINT8 ColorLabelDate = (date->ControlFocus) ? date->LabelFGColor:date->NSelLabelFGColor ;
	BOOLEAN bShowDay = StyleShowDay() ;
	UINTN dateFormat = StyleGetDateFormat() ;
	//gRT->GetTime(&Tm,NULL);
	UefiGetTime(&date->ControlData, &Tm);
	
	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if ( date->ControlData.ControlConditionalPtr != 0x0 )
	//{
		switch( CheckControlCondition( &date->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorDate = ColorLabelDate = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	NScolor = date->BGColor | ColorDate;
	SColor = date->SelBGColor | date->SelFGColor;

	// label
	t = HiiGetString( date->ControlData.ControlHandle, UefiGetPromptField(date->ControlData.ControlPtr));
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == t){
		t = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!t)
			return EFI_NOT_FOUND;
		EfiStrCpy(t,L" ");
	}
	// boundary overflow  check
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(date->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( date->Left , date->Top, 
				(UINTN)(date->LabelMargin - date->Left ),(UINTN) date->Height,
				t, date->BGColor | ColorLabelDate );
	}
	else
	{
		if ( (TestPrintLength(t) / (NG_SIZE)) > (UINTN)(date->LabelMargin - date->Left  )/*21*/ )
				t[date->LabelMargin - date->Left ] = L'\0';
	
		DrawStringWithAttribute( date->Left , date->Top, (CHAR16*)t, 
				date->BGColor | ColorLabelDate );
	}
	MemFreePointer ((VOID **)&t);

	day = _DateGetWeekDay( &Tm );

	t = HiiGetString( gHiiHandle, (bShowDay)? DayNames[day]:STRING_TOKEN(STR_EMPTY_STRING));
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == t){
		t = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!t)
			return EFI_NOT_FOUND;
		EfiStrCpy(t,L" ");
	}
	
	nIndex = TestPrintLength(t) / (NG_SIZE);
	nDateLen = TestPrintLength(t) / (NG_SIZE);
	nEFIDateLen = EfiStrLen(t);
	
	if ( t != NULL )
	{
		SPrint( text, sizeof(text), L"[%s ", t );
		text[nEFIDateLen + 1] = L' ';
		i = (bShowDay)? (nEFIDateLen + 2):(nEFIDateLen + 1);

		if ((dateFormat == DATE_STYLE_MMDDYYYY) || (dateFormat == DATE_STYLE_DDMMYYYY))
			EfiStrCpy(text+(i),L"XX/XX/XXXX]");
		else
			EfiStrCpy(text+(i),L"XXXX/XX/XX]");
	}
	MemFreePointer( (VOID **)&t );
	i = (bShowDay)? (nDateLen + 2):(nDateLen + 1) ; //(StyleShowDay()==TRUE)?2:1;
	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ , date->Top, (CHAR16*)text, 
			date->BGColor | ColorDate );

	nIndex = i;

	if ((dateFormat == DATE_STYLE_MMDDYYYY)||(dateFormat == DATE_STYLE_DDMMYYYY))
	{	
	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ + nIndex , date->Top, 
	( (date->Sel==0) && (date->ControlActive == TRUE ) ) ? DateTempNum :StrZeroPad((dateFormat == DATE_STYLE_MMDDYYYY)?Tm.Month:Tm.Day,txt), 
			(UINT8)((((date->Sel == 0) && (date->ControlFocus)) ? 
					 SColor/*date->SelBGColor | date->SelFGColor*/ : 
					 NScolor/*date->BGColor | ColorDate*/ )) );

	nIndex+=3;
	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ + nIndex , date->Top, 
	( (date->Sel==1) && (date->ControlActive == TRUE ) ) ? DateTempNum :StrZeroPad((dateFormat == DATE_STYLE_MMDDYYYY)?Tm.Day:Tm.Month,txt), 
			(UINT8)( (((date->Sel == 1) && (date->ControlFocus)) ? 
					  SColor/*date->SelBGColor | date->SelFGColor*/ :
					  NScolor/*date->BGColor | ColorDate*/ )) );

	nIndex+=3;
	if((Tm.Year < 1000) &&( atoi(DateTempNum, 10) < 1000))
		SPrint(txt,sizeof(txt),L"%04d",Tm.Year); //Update the date string when year is ZERO.

	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ + nIndex , date->Top, 
		( (date->Sel==2) && (date->ControlActive == TRUE ) ) ? DateTempNum :((Tm.Year < 1000) ?  txt : StrZeroPad( Tm.Year,txt)), 
			(UINT8)( (((date->Sel == 2) && (date->ControlFocus)) ? 
					  SColor/*date->SelBGColor | date->SelFGColor*/ :
					  NScolor/*date->BGColor | ColorDate*/ )) );
	}
	else 
	{

	if((Tm.Year < 1000) &&( atoi(DateTempNum, 10) < 1000))
		SPrint(txt,sizeof(txt),L"%04d",Tm.Year); //Update the date string when year is ZERO.
	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ + nIndex , date->Top, 
	( (date->Sel==0) && (date->ControlActive == TRUE ) ) ? DateTempNum :((Tm.Year < 1000) ?  txt : StrZeroPad( Tm.Year,txt)), 
			(UINT8)( (((date->Sel == 0) && (date->ControlFocus)) ? 
					  SColor/*date->SelBGColor | date->SelFGColor*/ :
					  NScolor/*date->BGColor | ColorDate*/ )) );

	nIndex+=5;
	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ + nIndex , date->Top, 
	( (date->Sel==1) && (date->ControlActive == TRUE ) ) ? DateTempNum :StrZeroPad((dateFormat == DATE_STYLE_YYYYDDMM)?Tm.Day:Tm.Month,txt), 
			(UINT8)( (((date->Sel == 1) && (date->ControlFocus)) ? 
					  SColor/*date->SelBGColor | date->SelFGColor*/ :
					  NScolor/*date->BGColor | ColorDate*/ )) );

	nIndex+=3;
	DrawStringWithAttribute( MarginLeft/*date->Left + date->LabelMargin*/ + nIndex , date->Top, 
	( (date->Sel==2) && (date->ControlActive == TRUE ) ) ? DateTempNum :StrZeroPad((dateFormat == DATE_STYLE_YYYYDDMM)?Tm.Month:Tm.Day,txt), 
			(UINT8)((((date->Sel == 2) && (date->ControlFocus)) ? 
					 SColor/*date->SelBGColor | date->SelFGColor*/ : 
					 NScolor/*date->BGColor | ColorDate*/ )) );
	}

	FlushLines(date->Top, date->Top);
	return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateInitialize
//
// Description:	Function to handle the date actions.
//
// Input:	DATE_DATA *date, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateHandleAction( DATE_DATA *date, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if(date->ControlActive)
			return Status;

        if (0 == date->ControlData.ControlFlags.ControlRefresh)         //EIP61650 If control not has refresh no need of proceeding
            return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;

		if ( --(date->Interval) == 0 )
		{
			// initialize the interval
			date->Interval = (UINT8)(date->ControlData.ControlFlags.ControlRefresh);
			return UefiRefershQuestionValueNvRAM(&(date->ControlData));
		}
		else
			return Status;
	}

	if ( ! date->ControlFocus )
		return Status;

    if (( Data->Input.Type == ACTION_TYPE_KEY )||(Data->Input.Type == ACTION_TYPE_MOUSE))
        return _DateHandleActionKeyMouse(date, Data);

	return Status;
}

EFI_STATUS _DateHandleActionKeyMouse(DATE_DATA *date,  ACTION_DATA *Data)
{
    CONTROL_ACTION Action;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_TIME Tm;
	AMI_EFI_KEY_DATA key = Data->Input.Data.AmiKey;
	UINTN dateFormat = StyleGetDateFormat() ;

    if(date->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;

    //Get time
	//gRT->GetTime( &Tm, NULL );
	UefiGetTime(&date->ControlData, &Tm);

    //Get mapping
	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
      Action = MapControlKeysHook(key);
	}
	else if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		{
		
			//EIP-123727 check whether MouseTop is within the Height and Width of Date Control or not
			if((Data->Input.Data.MouseInfo.Top >= (UINT32)date->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(date->Top+date->Height)) &&
		          (Data->Input.Data.MouseInfo.Left >= (UINT32)date->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(date->Left+date->Width)))//EIP-123727
			{
				Action = ControlActionSelect;		
			}
		}
	}

    switch(Action)
    {
        case ControlActionNextLeft:
#if SETUP_STYLE_AWARD
		if ( date->ControlActive )
			_DateUpdateEntry(date);

		if ( date->Sel == 0 )
			date->Sel = 2;
		else
			date->Sel--;

		Status = EFI_SUCCESS;		
		break;
#endif

        case ControlActionNextRight:
		if ( date->ControlActive )
			_DateUpdateEntry(date);

#if SETUP_STYLE_AWARD
		if ( date->Sel == 2 )
			date->Sel = 0;
		else
			date->Sel++;

		Status = EFI_SUCCESS;
#endif
		break;

        case ControlActionNextUp:
        case ControlActionNextDown:
            if ( date->ControlActive )
                _DateUpdateEntry(date);
	    break;

        case ControlActionAbort:
		if ( date->ControlActive )
		{
                	date->ControlActive = FALSE;
			Status = EFI_SUCCESS;
		}
		break;

        case ControlActionSelect:
		if(Data->Input.Type == ACTION_TYPE_MOUSE)
		NumericSoftKbdInit();		
		_DateUpdateEntry(date);
// for EZPORT: expressely to go to next entry in date control after hitting enter
#if SETUP_STYLE_AWARD
        break;
#endif

        case ControlActionNextSelection:
		if ( date->ControlActive )
			_DateUpdateEntry(date);

		if ( date->Sel == 2 )
			date->Sel = 0;
		else
			date->Sel++;

		Status = EFI_SUCCESS;
		break;

	case ControlActionPrevSelection:
		if ( date->ControlActive )
			_DateUpdateEntry(date);

		if ( date->Sel == 0 )
			date->Sel = 2;
		else
			date->Sel--;

			Status = EFI_SUCCESS;
		break;

        case ControlActionDecreament:
			if(date->ControlActive)
    		{
        		_DateUpdateEntry(date);
    		}
			_DateDecrease( date );
			date->ControlActive = TRUE;
			Status = EFI_SUCCESS;
   			break;

        case ControlActionIncreament:
			if(date->ControlActive)
    		{
     			_DateUpdateEntry(date);
    		}
			_DateIncrease( date );
			date->ControlActive = TRUE;
			Status = EFI_SUCCESS;
			break;

        case ControlActionNumeric:
            	if( !(date->ControlActive) )
		{
                	MemSet(DateTempNum, 10, 0x0);
			date->ControlActive = TRUE;
			switch(date->Sel)
			{
				case 0:
					if((dateFormat == DATE_STYLE_YYYYDDMM) || (dateFormat == DATE_STYLE_YYYYMMDD))
						SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year );	
					else if(dateFormat == DATE_STYLE_DDMMYYYY)
						SPrint(DateTempNum,sizeof(DateTempNum),L"%d",Tm.Day);	
					else
						SPrint(DateTempNum,sizeof(DateTempNum),L"%d",Tm.Month);			
					break;
				case 1:
					if((dateFormat == DATE_STYLE_DDMMYYYY) || (dateFormat == DATE_STYLE_YYYYMMDD))
						SPrint(DateTempNum,sizeof(DateTempNum),L"%d",Tm.Month);			
					else
						SPrint(DateTempNum,sizeof(DateTempNum),L"%d",Tm.Day);			
					break;
				case 2:
					if(dateFormat == DATE_STYLE_YYYYDDMM)
						SPrint(DateTempNum,sizeof(DateTempNum),L"%d",Tm.Month);	
					else if(dateFormat == DATE_STYLE_YYYYMMDD)
						SPrint(DateTempNum,sizeof(DateTempNum),L"%d",Tm.Day);	
					else
						SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year );			
					break;
			}
		}

		if(EfiStrLen(DateTempNum)>1)
			DateTempNum[0] =DateTempNum[1];

		if (
			( (2 == date->Sel) && (DATE_STYLE_MMDDYYYY == dateFormat || DATE_STYLE_DDMMYYYY == dateFormat) ) ||
			( (0 == date->Sel) && (DATE_STYLE_YYYYDDMM == dateFormat || DATE_STYLE_YYYYMMDD == dateFormat) )
			 )
		{
			DateTempNum[1] =DateTempNum[2];
			DateTempNum[2] =DateTempNum[3];
			DateTempNum[3] = key.Key.UnicodeChar;
		}else
			DateTempNum[1] = key.Key.UnicodeChar;

		Status = gDate.Draw(date);
        	break;

        default:
            if ( date->ControlActive )
                _DateUpdateEntry(date);
        	break;
	}
	
	if( (((!date->ControlActive)||(!IsMouseClickedonSoftkbd())) && (TSEMouseIgnoreMouseActionHook() == TRUE) )&&
		(((Data->Input.Type == ACTION_TYPE_KEY) &&
			((Action == ControlActionNextLeft) ||(Action == ControlActionNextRight) ||(Action == ControlActionNextUp) ||(Action == ControlActionNextDown) ||(Action == ControlActionPageUp) ||(Action == ControlActionPageDown) ||(Action == ControlActionAbort) ||(Action == ControlActionHome) ||(Action == ControlActionEnd) ||(CheckKeyinHotKeysList(key))) ) ||
			((Data->Input.Type == ACTION_TYPE_MOUSE)&&((!((Data->Input.Data.MouseInfo.Top >= (UINT32)date->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(date->Top+date->Height))&&(Data->Input.Data.MouseInfo.Left >= (UINT32)date->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(date->Left+date->Width))))||(Action == ControlActionAbort))))
	)
	{
		NumericSoftKbdExit();//EIP62763 : Check for softkbd presence and existing the numeric softkbd 
	}
		
	_DateUpdateHelp( date );
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateSetCallback
//
// Description:	Function to set callback.
//
// Input:		DATE_DATA *date, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateSetCallback( DATE_DATA *date, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateSetFocus
//
// Description:	Function to set the Date focus.
//
// Input:		DATE_DATA *date, BOOLEAN focus
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateSetFocus( DATE_DATA *date, BOOLEAN focus)
{
	if(focus != FALSE)
	{
		if ( CheckControlCondition( &date->ControlData ) )
			return EFI_UNSUPPORTED;
	}

	if( !(date->ControlFocus && focus) )
	{
		date->ControlFocus = focus;

		// set the selected field to Month
		date->Sel = 0;
		_DateUpdateHelp( date );
	}

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateSetPosition
//
// Description:	Function to set the date position.
//
// Input:		DATE_DATA *date, UINT16 Left, UINT16 Top
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateSetPosition( DATE_DATA *date, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( date, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateSetDimensions
//
// Description:	Function to set the date dimensions.
//
// Input:		 DATE_DATA *date, UINT16 Width, UINT16 Height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateSetDimensions( DATE_DATA *date, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( date, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateSetAttributes
//
// Description:	Function to set the date attributes.
//
// Input:		DATE_DATA *date, UINT8 FGColor, UINT8 BGColor
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateSetAttributes( DATE_DATA *date, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( date, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DateGetControlHeight
//
// Description:	Function to get the data label height.
//
// Input:	DATE_DATA *date, frame, UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DateGetControlHeight(DATE_DATA *date, VOID * frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		*height = 1;	
		Width = (UINT16)(date->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gControlLeftPad));

		text = HiiGetString( date->ControlData.ControlHandle, UefiGetPromptField(date->ControlData.ControlPtr) );		
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
// Procedure:	_DateGetWeekDay
//
// Description:	Function to get weekday.
//
// Input:		EFI_TIME *tm
//
// Output:		UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _DateGetWeekDay( EFI_TIME *tm )
{
	//EIP-75384 Static Code
    //EIP-80092 
	INTN d, m, y, c;
	INTN w;

	d = tm->Day;
	m = tm->Month - 2;
	y = tm->Year;

	if ( m <= 0 )
	{
		m += 12;
		y--;
	}

	c = y / 100;
	y %= 100;

	w = d + y + (5 * c) + ((13 * m - 1) / 5) + (y / 4) + (c / 4);

	return w % 7;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DateDecrease
//
// Description:	Function to decrement date.
//
// Input:		DATE_DATA *date
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DateDecrease( DATE_DATA *date )
{
	EFI_TIME Tm;
	BOOLEAN Case_day = FALSE;
	UINTN dateFormat = StyleGetDateFormat() ;

	//gRT->GetTime( &Tm, NULL );
	UefiGetTime(&date->ControlData, &Tm);

	switch ( date->Sel )
	{
		case 0:
			if((dateFormat == DATE_STYLE_YYYYDDMM) || (dateFormat == DATE_STYLE_YYYYMMDD)){
				Tm.Year--;
				SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year); //Update the static date string
			}else if(dateFormat == DATE_STYLE_DDMMYYYY)
			{	
				if ( Tm.Day > 1 )
					Tm.Day--;
				else
					Tm.Day = 31; // this is to find out wich is the highest day for the month.
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
				Case_day = TRUE;
			}else{
				if ( Tm.Month > 1 )
					Tm.Month--;
				else
					Tm.Month = 12;
				StrZeroPad(Tm.Month, DateTempNum); //Update the static date string
			}
			break;
		case 1:
			if((dateFormat == DATE_STYLE_DDMMYYYY) || (dateFormat == DATE_STYLE_YYYYMMDD))
			{	
				if ( Tm.Month > 1 )
					Tm.Month--;
				else
					Tm.Month = 12;
				StrZeroPad(Tm.Month, DateTempNum); //Update the static date string
			}else{
				if ( Tm.Day > 1 )
					Tm.Day--;
				else
					Tm.Day = 31; // this is to find out wich is the highest day for the month.
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
				Case_day = TRUE;
			}
			break;
		case 2:
			if(dateFormat == DATE_STYLE_YYYYDDMM)
			{	
				if ( Tm.Month > 1 )
					Tm.Month--;
				else
					Tm.Month = 12;
				StrZeroPad(Tm.Month, DateTempNum); //Update the static date string
			}else if(dateFormat == DATE_STYLE_YYYYMMDD){
				if ( Tm.Day > 1 )
					Tm.Day--;
				else
					Tm.Day = 31; // this is to find out wich is the highest day for the month.
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
				Case_day = TRUE;
			}else{
				Tm.Year--;
					if(Tm.Year > 9999)
						Tm.Year = 9999;
					SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year); //Update the static date string
			}
			break;
	}

	while ( UefiSetTime(&date->ControlData, &Tm) != EFI_SUCCESS )
    {
		if(Tm.Day > 28){
			Tm.Day--; //May be this month does not support days greater than 28
			if(Case_day == TRUE)
			  StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
		} else{
			//EIP 79487:SetTime failed due to year decremented beyound the range
			Tm.Year++;
			SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year); //Update the static date string
            UefiSetTime(&date->ControlData, &Tm);
			break; //SetTime failed due to some other error keep time unchanged.
		}
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DateIncrease
//
// Description:	Function to increment date.
//
// Input:		DATE_DATA *date
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DateIncrease( DATE_DATA *date )
{
	EFI_TIME Tm;
	UINTN dateFormat = StyleGetDateFormat() ;
	BOOLEAN Case_day = FALSE;

	//gRT->GetTime( &Tm, NULL );
	UefiGetTime(&date->ControlData, &Tm);

	switch ( date->Sel )
	{
		case 0:
			if((dateFormat == DATE_STYLE_YYYYDDMM) || (dateFormat == DATE_STYLE_YYYYMMDD)){
				Tm.Year++;
				SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year); //Update the static date string
			} else if(dateFormat == DATE_STYLE_DDMMYYYY){
				if(Tm.Day < 31){
					Tm.Day++;
				} else{
					Tm.Day = 1;
				}
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
				Case_day = TRUE;
			} else{
				if ( Tm.Month < 12 )
					Tm.Month++;
				else 
					Tm.Month = 1;
				StrZeroPad(Tm.Month, DateTempNum); //Update the static date string
			}
			break;
		case 1:
			if((dateFormat == DATE_STYLE_DDMMYYYY) || (dateFormat == DATE_STYLE_YYYYMMDD))
			{	
				if ( Tm.Month < 12 )
					Tm.Month++;
				else 
					Tm.Month = 1;
				StrZeroPad(Tm.Month, DateTempNum); //Update the static date string
			} else{
				if(Tm.Day < 31){
					Tm.Day++;
				} else{
					Tm.Day = 1;
				}
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
				Case_day = TRUE;
			}
			break;
		case 2:
			if(dateFormat == DATE_STYLE_YYYYDDMM)
			{
				if ( Tm.Month < 12 )
					Tm.Month++;
				else 
					Tm.Month = 1;
				StrZeroPad(Tm.Month, DateTempNum); //Update the static date string
			}else if(dateFormat == DATE_STYLE_YYYYMMDD){
				if(Tm.Day < 31){
					Tm.Day++;
				} else{
					Tm.Day = 1;
				}
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
				Case_day =  TRUE;
			}else{
				Tm.Year++;
				if(Tm.Year > 9999)
					Tm.Year = 0;
				SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year); //Update the static date string
			}
			break;
	}

    //if ( gRT->SetTime( &Tm ) != EFI_SUCCESS )
    if ( UefiSetTime(&date->ControlData, &Tm) != EFI_SUCCESS )
	{
        //SetTime may be failed because of invalid day try with
        //day = 1
			Tm.Day = 1;
			if(Case_day == TRUE)//EIP 79487 
				StrZeroPad(Tm.Day, DateTempNum); //Update the static date string
			if(UefiSetTime(&date->ControlData, &Tm) != EFI_SUCCESS)
			{
				Tm.Year--;
				SPrint(DateTempNum,sizeof(DateTempNum),L"%04d",Tm.Year); //EIP 79487:Update the static date string
				UefiSetTime(&date->ControlData, &Tm); //If this second SetTime also fails dont worry the time didnt change
			}
		
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DateUpdateEntry
//
// Description:	Function to update entry.
//
// Input:		DATE_DATA *date
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DateUpdateEntry(DATE_DATA *date)
{
	EFI_TIME Tm = {0};
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN dateFormat = StyleGetDateFormat() ;

	//gRT->GetTime( &Tm, NULL );
	UefiGetTime(&date->ControlData, &Tm);

	if(date->ControlActive)
	{
		// focus stays on the selection becuase we just edited it
		switch(date->Sel)
		{
		case 0:
			if((dateFormat == DATE_STYLE_YYYYDDMM) || (dateFormat == DATE_STYLE_YYYYMMDD))
				Tm.Year = (UINT16)atoi(DateTempNum, 10);
			else if(dateFormat == DATE_STYLE_DDMMYYYY)
				Tm.Day = (UINT8)atoi(DateTempNum, 10);
			else
                Tm.Month = (UINT8)atoi(DateTempNum, 10);
			break;
		case 1:
			if((dateFormat == DATE_STYLE_DDMMYYYY) || (dateFormat == DATE_STYLE_YYYYMMDD))
				Tm.Month = (UINT8)atoi(DateTempNum, 10);
			else
    	        Tm.Day = (UINT8)atoi(DateTempNum, 10);
			break;
		case 2:
			if(dateFormat == DATE_STYLE_YYYYDDMM)
				Tm.Month = (UINT8)atoi(DateTempNum, 10);
			else if(dateFormat == DATE_STYLE_YYYYMMDD)
				Tm.Day = (UINT8)atoi(DateTempNum, 10);
			else
    	        Tm.Year = (UINT16)atoi(DateTempNum, 10);
			break;
		}
		
		UefiPreControlUpdate(&(date->ControlData));
		UefiSetTime(&date->ControlData, &Tm);
		//For interactive date control invoke the formcallback functions
		if(UefiIsInteractive(&date->ControlData)){
			UINT8 Flags = UefiGetFlagsField(date->ControlData.ControlPtr) ;
			
			if(CheckDateFlags(Flags))
			{
				//for storage type QF_DATE_STORAGE_NORMAL generate time in EFI_HII_DATE format
				
				//Call the callbacks passing the generated input value and value size
				Status = CallFormCallBack(&date->ControlData, UefiGetControlKey(&date->ControlData), 0, AMI_CALLBACK_CONTROL_UPDATE);
			}// else {
				//This case would be handled by UefiSetTime() outside using runtime services
			//}
		}
				
                date->ControlActive = FALSE;
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DateUpdateHelp
//
// Description:	Function to update help.
//
// Input:		DATE_DATA *date
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DateUpdateHelp( DATE_DATA *date )
{
	UINT16	helpToken = date->ControlData.ControlHelp;
	UINT16 Min,Max;
	UINTN dateFormat = StyleGetDateFormat() ;

	switch ( date->Sel )
	{
		case 0:
			if((dateFormat == DATE_STYLE_YYYYDDMM) || (dateFormat == DATE_STYLE_YYYYMMDD))
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_YEAR,&helpToken,&Min,&Max);
			else if(dateFormat == DATE_STYLE_DDMMYYYY)
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_DAY,&helpToken,&Min,&Max);
			else
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_MONTH,&helpToken,&Min,&Max);
			break;
		case 1:
			if((dateFormat == DATE_STYLE_DDMMYYYY) || (dateFormat == DATE_STYLE_YYYYMMDD))
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_MONTH,&helpToken,&Min,&Max);
			else
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_DAY,&helpToken,&Min,&Max);
			break;
		case 2:
			if(dateFormat == DATE_STYLE_YYYYDDMM)
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_MONTH,&helpToken,&Min,&Max);
			else if(dateFormat == DATE_STYLE_YYYYMMDD)
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_DAY,&helpToken,&Min,&Max);
			else
				UefiGetDateTimeDetails(date->ControlData.ControlPtr,AMI_DATE_YEAR,&helpToken,&Min,&Max);
			break;
		default:
			break;
	}

	date->ControlData.ControlHelp = helpToken;
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
