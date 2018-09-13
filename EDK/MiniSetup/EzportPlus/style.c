//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/EzportPlus/style.c $
//
// $Author: Premkumara $
//
// $Revision: 4 $
//
// $Date: 5/02/14 4:05a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/EzportPlus/style.c $
// 
// 4     5/02/14 4:05a Premkumara
// [TAG]  		EIP151966
// [Category]  	Improvement
// [Description]  	Added the implementation for getting the BIOS build
// year dynamically 
// from TimeStamp.h file and updated the Build year in copyright message
// in both Setup and POST.
// [Files]  		style.c,style.c,style.c,notify.c,minisetupext.c,CommonHelper
// .c,
// AmiTSEStr.uni,AMITSE.mak
// 
// 3     10/18/12 6:07a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:43p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 2     6/23/11 5:46a Rajashakerg
// [TAG]  		EIP63073  
// [Category]  	New Feature
// [Description]  	Source modules in TSE should get the version details
// from binary in run time not at build time
// [Files]  		CommonHelper.c, minisetupext.c, notify.c, Ezport\style.c,
// EzportPlus\style.c, Legacy\style.c
// 
// 1     3/28/11 11:51p Madhans
// [TAG]  		EIP54968
// [Category]  	Improvement
// [Description]  	To Support different style modules in TSE generically
// [Files]  		Ezport module updated. EzportPlus and Legacy Styles Modules
// added.
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:15a Mallikarjunanv
// updated year in copyright message
// 
// 5     2/04/10 11:16p Madhans
// Navgation help for Mouse Added
// 
// 4     1/09/10 6:13a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 3     6/23/09 6:54p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 2:36p Blaines
// Update coding standard
// 
// 1     6/04/09 8:05p Madhans
// 
// 3     5/07/09 10:35a Madhans
// Changes after Bin module
// 
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:15p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		style.c
//
// Description:	Contains style override functions.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"

extern UINT8 gVerticalMainDivider ;
extern UINT8 gHorizontalHelpDivider ;
extern UINT16 gStrNavToken;

VOID _StyleAddSpacing( FRAME_DATA *frame );
VOID GetTseBuildVersion(UINTN *TseMajor, UINTN *TseMinor, UINTN *TseBuild);
VOID GetTseBuildYear(UINT16 *TseBuildYear);//EIP 151966 : Use BIOS build year for copyright message

#if SETUP_STYLE_EZPORTPLUS



STYLECOLORS  Colors =
{
	TEXT_COLOR, 			//EFI_WHITE,	//FGColor
	PAGE_BGCOLOR,					//BGColor
	NON_FOCUS_COLOR, 		//EFI_BLUE,	//secondary FGcolor
	PAGE_BGCOLOR,					//secondary BGColor
	CONTROL_FOCUS_COLOR, 		//EFI_WHITE,	//SelFGColor
	PAGE_BGCOLOR,					//SelBGColor
	CONTROL_NON_FOCUS_COLOR,	//EFI_BLUE,	//NSelFGColor
	PAGE_BGCOLOR,					//NSelBGColor
	PAGE_BGCOLOR,					//LabelBGColor
	LABEL_FOCUS_COLOR,		//EFI_WHITE,	//LabelFGColor
	LABEL_NON_FOCUS_COLOR,		//EFI_BLUE,	//NSelLabelFGColor
	EDIT_BGCOLOR,					//EditBGColor
	EDIT_FGCOLOR,		 	//EFI_WHITE,	//EditFGColor
	POPUP_FGCOLOR,					//popupFGColor
	POPUP_BGCOLOR					//popupBGColor
};
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleHandleControlOverflow	
//
// Description:	Function to handle contro overflow
//
// Input:		FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OverRideStyleHandleControlOverflow( FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
  	CONTROL_DATA *tempcontrol;
  	UINT16 i=0,Height=0;
  	UINT8	BORDER=(frame->FrameData.Border==TRUE)?1:0 ;

    	// show scrollbar if neccessary
    	frame->UseScrollbar = FALSE;

	for(i = 0; i < count; i++)
	{
		tempcontrol = (CONTROL_DATA*)(frame->ControlList[i]);
	        if( (Height + tempcontrol->Height ) <= frame->FrameData.Height-2*BORDER )
	        {
	            Height = Height + tempcontrol->Height;
	            frame->LastVisibleCtrl = i;
	        }
	        else
	        {
	            Status = EFI_SUCCESS;
	            break;
	        }
	}

	return Status;
}

static AMI_IFR_MENU gMenuData = {CONTROL_TYPE_MENU,2};
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleInitializeFrame	
//
// Description:	Function to initialize frame
//
// Input:		FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OverRideStyleInitializeFrame( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data )
{
	EFI_STATUS	Status = EFI_INVALID_PARAMETER;
	UINT8	justify = JUSTIFY_LEFT /*, BORDER=(frame->FrameData.Border==TRUE)?1:0*/ ;
	STYLECOLORS saveColors ;
	
	CONTROL_INFO dummy;

	UINT32 FrameType = frame->FrameData.FrameType ;
	
	saveColors = Colors ;

	//Allows controls to match the Background Color of the Frame
	Colors.BGColor		=	frame->FrameData.BGColor ;	
	Colors.SecBGColor	=	frame->FrameData.BGColor ;
	Colors.SelBGColor	=	frame->FrameData.BGColor ;
	Colors.NSelBGColor	=	frame->FrameData.BGColor ;
	Colors.LabelBGColor	=	frame->FrameData.BGColor ;
	Colors.PopupBGColor =	frame->FrameData.BGColor ;

	switch ( FrameType )
	{
		case MAIN_FRAME:
			if(LABEL_FOCUS_COLOR != FOCUS_COLOR)
				Colors.LabelFGColor = LABEL_FOCUS_COLOR ;

			if(CONTROL_FOCUS_COLOR != FOCUS_COLOR)
				Colors.SelFGColor = CONTROL_FOCUS_COLOR;

			if(LABEL_NON_FOCUS_COLOR != NON_FOCUS_COLOR)
				Colors.NSelLabelFGColor = LABEL_NON_FOCUS_COLOR ;

			if(CONTROL_NON_FOCUS_COLOR != NON_FOCUS_COLOR)
				Colors.NSelFGColor = CONTROL_NON_FOCUS_COLOR ;
			
            if (frame->PageID == FIRST_PAGE_ID_INDEX)
            {
                // Reset frame width
                frame->FrameData.Width = (UINT8)(gMaxCols - gLabelLeftMargin - 1);

                // Reset clear frame area width
                gBS->FreePool(frame->BlankLine);
                frame->BlankLine = EfiLibAllocateZeroPool( sizeof(CHAR16) * (frame->FrameData.Width + 1) );
                if ( frame->BlankLine != NULL )
                    MemFillUINT16Buffer( frame->BlankLine, frame->FrameData.Width, L' ' );
            }
			Status = _FrameAddControls( frame, data );
			break;

		case SUBTITLE_FRAME:
			Colors.SecBGColor	=	SELECTED_MENU_BGCOLOR ;
			Colors.SecFGColor	=	SELECTED_MENU_FGCOLOR ;
			Colors.PopupBGColor =	MENU_BGCOLOR ;
			Colors.PopupFGColor =	MENU_FGCOLOR ;

	        MemSet( &dummy, sizeof(dummy), 0 );
	        dummy.ControlHandle = gHiiHandle;
			dummy.ControlType = CONTROL_TYPE_MENU;
	        dummy.ControlPtr = (VOID*)&gMenuData;
			dummy.ControlPageID = data->PageID; 
			dummy.ControlFlags.ControlVisible = TRUE;
	        Status=gFrame.AddControl(frame,&dummy);
			break;

		case TITLE_FRAME:

		
        case NAV_FRAME:
             
			 justify = JUSTIFY_CENTER;
			Status = _FrameAddTitle( frame, FrameType, data );
			if ( ! EFI_ERROR( Status ) )
			{
				MEMO_DATA *memo = (MEMO_DATA *)frame->ControlList[0];
				
				if(FrameType == NAV_FRAME )
				{
                    memo->ControlData.ControlPtr= (VOID*) UefiCreateSubTitleTemplate(STRING_TOKEN(STR_NAV_STRINGS_5));
					if ( gMaxCols <= 80 )
					{
						gMaxRows=25;
                    	memo->ControlData.ControlPtr= (VOID*) UefiCreateSubTitleTemplate(STRING_TOKEN(STR_NAV_STRINGS_6));
					}
				}
				if (FrameType == HELPTITLE_FRAME)
					justify = JUSTIFY_CENTER;   // EIP25281.style +
				gMemo.SetJustify( memo, justify );
			}

			 break;
		case HELP_FRAME:

			 justify = JUSTIFY_LEFT;
		case HELPTITLE_FRAME:
			Status = _FrameAddTitle( frame, FrameType, data );
			if ( ! EFI_ERROR( Status ) )
			{
				MEMO_DATA *memo = (MEMO_DATA *)frame->ControlList[0];
				
				if(FrameType == NAV_FRAME )
				{
                    memo->ControlData.ControlPtr= (VOID*) UefiCreateSubTitleTemplate(STRING_TOKEN(STR_NAV_STRINGS_5));
					if ( gMaxCols <= 80 )
					{
                    	memo->ControlData.ControlPtr= (VOID*) UefiCreateSubTitleTemplate(STRING_TOKEN(STR_NAV_STRINGS_6));
					}
				}
				if (FrameType == HELPTITLE_FRAME)
					justify = JUSTIFY_CENTER;   // EIP25281.style +
				gMemo.SetJustify( memo, justify );
			}
			break;

		case SCROLLBAR_FRAME:
			// not implemented at this time
			Status = EFI_SUCCESS;
			break;

		default:
			//Status = StyleInitializeOemFrame( frame, frame->FrameData.FrameType, data ) ;
			break;
	}


	Colors = saveColors;

	// initialize frame scroll colors
	frame->FrameData.ScrlFGColor = SCROLLBAR_FGCOLOR ; 
	frame->FrameData.ScrlBGColor = SCROLLBAR_BGCOLOR ; 
	frame->FrameData.ScrlUpFGColor = SCROLLBAR_UPARROW_FGCOLOR ; 
	frame->FrameData.ScrlUpBGColor = SCROLLBAR_UPARROW_BGCOLOR ;
	frame->FrameData.ScrlDnFGColor = SCROLLBAR_DOWNARROW_FGCOLOR ; 
	frame->FrameData.ScrlDnBGColor = SCROLLBAR_DOWNARROW_BGCOLOR ;

	return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleGetNavToken	
//
// Description:	Function to get navigation frame token
//
// Input:		UINT32 page number
//
// Output:		UINT16 token 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 OverRideStyleGetNavToken( UINT32 page )
{
    UINT16 Token=0; 
	
	Token = STRING_TOKEN(STR_NAV_STRINGS_5);
	
    if ( gMaxCols <= 80 )
	{
	    	Token = STRING_TOKEN(STR_NAV_STRINGS_6);
	}
    
    return Token ;//    return gStrNavToken;
}



static AMI_IFR_LABEL gFailSafeLabel = { 0, 0, STRING_TOKEN(STR_LOAD_FAILSAFE), STRING_TOKEN(STR_LOAD_FAILSAFE_HELP) };
static AMI_IFR_LABEL gOptimalLabel = { 0, 0, STRING_TOKEN(STR_LOAD_OPTIMAL), STRING_TOKEN(STR_LOAD_OPTIMAL_HELP) };
static AMI_IFR_LABEL gSaveExitLabel = { 0, 0, STRING_TOKEN(STR_SAVE_EXIT), STRING_TOKEN(STR_SAVE_EXIT_HELP) };
static AMI_IFR_LABEL gExitLabel = { 0, 0, STRING_TOKEN(STR_EXIT), STRING_TOKEN(STR_EXIT_HELP) };
static AMI_IFR_LABEL gSaveResetLabel = { 0, 0, STRING_TOKEN(STR_SAVE_RESET), STRING_TOKEN(STR_SAVE_RESET_HELP) };
static AMI_IFR_LABEL gResetLabel = { 0, 0, STRING_TOKEN(STR_RESET), STRING_TOKEN(STR_RESET_HELP) };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleAddAdditionalControls	
//
// Description:	Function to add additional controls
//
// Input:		FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OverRideStyleAddAdditionalControls( FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus )
{
	EFI_STATUS Status = EFI_SUCCESS;
	CONTROL_DATA **control;
	UINT32	i;

	if ( frame->PageID != 0 ) 
		return Status;

	control = frame->ControlList;
	  
	for ( i = 0; i < frame->ControlCount; i++, control++ )
	{
		(*control)->Methods->Destroy( *control, TRUE );
	}

	// initialize counter of control in frame and set focus to false (at this point the are no controls in the frame)
	frame->ControlCount =0;
	frame->NullCount=0;
	focus=0;
	controlNumber=0;
	
	// add controls for boot manager, language, failsafe, optimal, save & exit, exit without saving
/*	Status = _StyleAddControl( frame, CONTROL_TYPE_SUBMENU, &gBootManagerRef, &controlNumber, &focus );
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = _StyleAddControl( frame, CONTROL_TYPE_SUBMENU, &gLanguageRef, &controlNumber, &focus );
	if ( EFI_ERROR( Status ) )
		return Status;
*/
	Status = _StyleAddControl( frame, CONTROL_TYPE_LABEL, &gFailSafeLabel, &controlNumber, &focus );
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = _StyleAddControl( frame, CONTROL_TYPE_LABEL, &gOptimalLabel, &controlNumber, &focus );
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = _StyleAddControl( frame, CONTROL_TYPE_LABEL, &gSaveExitLabel, &controlNumber, &focus );
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = _StyleAddControl( frame, CONTROL_TYPE_LABEL, &gExitLabel, &controlNumber, &focus );

	Status = _StyleAddControl( frame, CONTROL_TYPE_LABEL, &gSaveResetLabel, &controlNumber, &focus );
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = _StyleAddControl( frame, CONTROL_TYPE_LABEL, &gResetLabel, &controlNumber, &focus );

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleSelectFirstDisplayPage	
//
// Description:	Function to set first page display
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OverRideStyleSelectFirstDisplayPage( VOID )
{
	gApp->CurrentPage = 1;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleUpdateVersionString	
//
// Description:	Function to update version string
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OverRideStyleUpdateVersionString( VOID )
{
	CHAR16 *string = NULL, *newString = NULL;
	UINTN length, TseMajor,TseMinor, TseBuild;
	UINT16 TseBuildYear=0;
	UINTN i;

	for ( i = 0; i < gLangCount; i++ )
	{
		string = HiiGetStringLanguage( gHiiHandle, STRING_TOKEN(STR_MAIN_COPYRIGHT), gLanguages[i].Unicode );
		if ( string == NULL )
			return;

		length = EfiStrLen(string) + 10;
		newString = EfiLibAllocateZeroPool( length * sizeof(CHAR16) );
		if ( newString != NULL )
		{
		//EIP 63073 : Source modules in TSE should get the version details from binary in run time not at build time
			GetTseBuildVersion(&TseMajor,&TseMinor,&TseBuild);
			//EIP 151966 : Use BIOS build year for copyright message
			GetTseBuildYear(&TseBuildYear);
			SPrint( newString, length * sizeof(CHAR16), string, TseMajor, TseMinor, TseBuild,TseBuildYear );
			HiiChangeStringLanguage( gHiiHandle, STRING_TOKEN(STR_MAIN_COPYRIGHT), gLanguages[i].Unicode, newString );
		}

		MemFreePointer( (VOID **)&newString );
		MemFreePointer( (VOID **)&string );
		//EIP 151966 : Use BIOS build year for copyright message
		string = HiiGetStringLanguage( gHiiHandle, STRING_TOKEN(STR_MAIN_TITLE), gLanguages[i].Unicode );
		if ( string == NULL )
			return;
		length = EfiStrLen(string) + 10;
		newString = EfiLibAllocateZeroPool( length * sizeof(CHAR16) );
		if ( newString != NULL )
		{
			//EIP 151966 : Use BIOS build year for copyright message
			GetTseBuildYear(&TseBuildYear);
			SPrint( newString, length * sizeof(CHAR16), string, TseBuildYear );
			HiiChangeStringLanguage( gHiiHandle, STRING_TOKEN(STR_MAIN_TITLE), gLanguages[i].Unicode, newString );
		}
		MemFreePointer( (VOID **)&newString );
		MemFreePointer( (VOID **)&string );
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleFrameDrawable	
//
// Description:	Function to determine if frame is drawable
//
// Input:		FRAME_DATA *frame
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OverRideStyleFrameDrawable( FRAME_DATA *frame )
{
	EFI_STATUS Status = EFI_SUCCESS;
    static UINTN TempRightAreaWidth = 0;
    
    if (frame->PageID == FIRST_PAGE_ID_INDEX)
    {
        
        switch ( frame->FrameData.FrameType )
        {            
            // Hidden NAV and HELP frame
            case HELP_FRAME:
            case HELPTITLE_FRAME:
                Status = EFI_UNSUPPORTED;
                break;

            // Set right area width
            case MAIN_FRAME:
                if (TempRightAreaWidth == 0)
                    {
                        // Set right area width
                        TempRightAreaWidth = gControlRightAreaWidth;
                        gControlRightAreaWidth = gMaxCols - gControlLeftMargin - gLabelLeftMargin - 2;
                    }
                break;
        }

        return Status;
    }
    if (TempRightAreaWidth != 0)
    {
        gControlRightAreaWidth = TempRightAreaWidth;
        TempRightAreaWidth = 0;
    }
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_StyleAddSpacing	
//
// Description:	Function to add spacing
//
// Input:		FRAME_DATA *frame
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _StyleAddSpacing( FRAME_DATA *frame )
{
	_StyleAddControl( frame, CONTROL_TYPE_NULL, NULL, NULL, NULL );
	if ( frame->ControlCount == 7 )
		_StyleAddControl( frame, CONTROL_TYPE_NULL, NULL, NULL, NULL );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_StyleAddControl	
//
// Description:	Function to add controls
//
// Input:		FRAME_DATA *frame, UINT16 type, VOID *data, UINT32 *controlNumber, BOOLEAN *focus
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _StyleAddControl( FRAME_DATA *frame, UINT16 type, VOID *data, UINT32 *controlNumber, BOOLEAN *focus )
{
	EFI_STATUS Status;
	CONTROL_INFO dummy;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;

	dummy.ControlType = type;
	dummy.ControlPtr = (VOID*)data;
	dummy.ControlFlags.ControlVisible = TRUE;

	Status = gFrame.AddControl( frame, &dummy );
	if ( EFI_ERROR( Status ) )
		return Status;

	if ( type != CONTROL_TYPE_NULL )
	{
		if ( ! *focus )
		{
			if ( _FrameSetControlFocus( frame, *controlNumber ) )
			{
				frame->CurrentControl = *controlNumber;
				*focus = TRUE;
			}
		}

		(*controlNumber)++;
	}

	return Status;
}
#endif
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
