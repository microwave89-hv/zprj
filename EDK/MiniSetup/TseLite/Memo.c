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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Memo.c $
//
// $Author: Arunsb $
//
// $Revision: 15 $
//
// $Date: 3/18/13 1:24a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Memo.c $
// 
// 15    3/18/13 1:24a Arunsb
// [TAG]  		EIP118306
// [Category]  	Improvement
// [Description]  	Support for grayout subtitle control
// [Files]  		Memo.c
// 
// 14    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 12    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 13    4/04/12 12:34a Rajashakerg
// [TAG]  		EIP83705 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Help page scroll bar not moving till end for the "Setup
// question completion timeout" control in "Advanced -> PCI Express GEN2
// settings".
// [RootCause]  	Scrollbar calculation for the help frame are improper.
// [Solution]  	provided proper value for the scrollbar.
// [Files]  		Memo.c
// 
// 12    12/01/11 1:45a Premkumara
// [TAG]  		EIP73236
// [Category]  	Improvement
// [Description]  	Large amounts of allocated memory are not freed
// [Files]  		Expression.c, PopupEdit.c, Popup.c, MessageBox.c, Menu.c,
// Memo.c, 
// 
// 11    11/21/11 8:52a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupSel.c, PopupString.c, SubMenu.c, Text.c.
// 
// 10    11/14/11 6:55p Blaines
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
// 9     6/29/11 12:49p Rajashakerg
// [TAG]  		EIP47086
// [Category]  	New Feature
// [Description]  	Right clicking from the Main page is not exiting from
// BIOS setup.
// 
// [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
// Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
// EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
// EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
// Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
// Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
// application.h, application.c, commonoem.h, CommonHelper.c
// 
// 8     3/09/11 7:23p Madhans
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
// 7     2/03/11 8:20p Madhans
// [TAG] - EIP 50956   
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- If we leave the Setup page for 2 or more days. The system
// may hang/Crash.
// [Rootcause] - Memory leaks
// [Solution]- Memeory freed.
// [Files] - ctrlcond.c, memo.c and expression.c 
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
// 6     1/22/10 6:14p Blaines
// EIP #33837 - Setup appearance corrupted if additional subtitles added
// Fix - Prevent memo draw if supressed condition
// 
// 5     1/09/10 6:40a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     10/28/09 5:38p Madhans
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
// 5     5/18/09 12:21p Blaines
// Fix Help Frame (memo) text scroll
// 
// 4     5/12/09 5:14p Blaines
// Patch for help text scroll issue
// 
// 3     5/07/09 10:36a Madhans
// Changes after Bin module
// 
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

#include "minisetup.h"

MEMO_METHODS gMemo =
{
	MemoCreate,
	MemoDestroy,
	MemoInitialize,
	MemoDraw,
	MemoHandleAction,
	MemoSetCallback,
	MemoSetFocus,
	MemoSetPosition,
	MemoSetDimensions,
	MemoSetAttributes,
	MemoGetControlHeight,
	MemoSetJustify
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoCreate
//
// Description:	Function to create a Memo, which uses the Control Functions.
//
// Input:	MEMO_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoCreate( MEMO_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(MEMO_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gMemo;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoDestroy
//
// Description:	Function to Destroy a Memo, which uses the Control Functions.
//
// Input:	MEMO_DATA *memo, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoDestroy( MEMO_DATA *memo, BOOLEAN freeMem )
{
	if(NULL == memo)
	  return EFI_SUCCESS;

	gControl.Destroy( memo, FALSE );

    if( freeMem ){
        MemFreePointer( (VOID **)&memo->EmptyString ); //EIP-73236 Free the allocated memory for the EmptyString field
		MemFreePointer( (VOID **)&memo );
    }

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoInitialize
//
// Description:	Function to Initialize a Memo, which uses the Control Functions.
//
// Input:	MEMO_DATA *memo, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoInitialize( MEMO_DATA *memo, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( memo, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	SetControlColorsHook( &(memo->BGColor), &(memo->FGColor), NULL, NULL ,NULL, NULL ,
	                      NULL , NULL,
						  NULL, NULL ,
						  NULL,NULL ,NULL,NULL, NULL );
	StyleGetSpecialColor( CONTROL_TYPE_MEMO, &(memo->FGColor)) ;
	memo->Interval = (UINT8)(memo->ControlData.ControlFlags.ControlRefresh);

	memo->Justify = JUSTIFY_LEFT;

	//[EIP:19479]RB:<Add>
	// initialization of ScrollBarPosition
	memo->ScrollBarPosition = 0;
	//[EIP:19479]RB:<Add>


	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoDraw
//
// Description:	Function to draw a Memo.
//
// Input:	MEMO_DATA *memo
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoDraw( MEMO_DATA *memo )
{
	CHAR16 *text = NULL, *newText = NULL;
	CHAR16 *line;
	UINT16 pos, height = 0;

	UINT16  TempPos = 0;
	BOOLEAN bScrollBar = FALSE;

	// check conditional ptr if necessary
	//EIP #33837 - Setup appearance corrupted if additional subtitles added
	// Fix - Prevent memo draw if supressed condition
    
    //EIP 75486 Support grayout condition for readonly controls
	//if( memo->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &memo->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				//Status = EFI_WARN_WRITE_FAILURE;
				memo->FGColor = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}
	
	text = HiiGetString( memo->ControlData.ControlHandle,UefiGetTitleField( (VOID *)memo->ControlData.ControlPtr));

	if ( text == NULL )
		return EFI_OUT_OF_RESOURCES;

	if ( EfiStrLen(text) == 0)
    {
        // String is empty but memory is allocated.
		MemFreePointer( (VOID **)&text );
		return EFI_OUT_OF_RESOURCES;
    }

	// clear out old wrapped string
	for ( pos = 0; pos < memo->Height; pos++ )
		DrawStringWithAttribute( memo->Left, memo->Top + pos, memo->EmptyString, memo->FGColor | memo->BGColor );

	// XXX: this wrapping code is probably not compatible with all languages
	newText = StringWrapText( text, memo->Width, &height );
	if(height == 0)
		return EFI_OUT_OF_RESOURCES;


	// where height is the total number of Lines if it is greater than memo->Height(14)
	// then scroll bar need or not needed.

	bScrollBar = ( (height > memo->Height) && (memo->ParentFrameType == HELP_FRAME /*memo->Top == MAIN_TOP*/)  ) ? 1 : 0;

	if( memo->ScrollBarPosition > (height - memo->Height) )
		memo->ScrollBarPosition = (height - memo->Height);
	
	if ( newText != text )
		MemFreePointer( (VOID **)&text );

	line = newText;

	// Draw complete strings in a help frame. Limits upto height of the string.
	for ( pos = 0; pos < height; pos++ )
	{
		CHAR16 save;

		text = line;
		if ( *line == L'\0' )
			break;

		while ( ( *line != L'\n' ) &&( *line != L'\r' ) && ( *line != L'\0' ) )
			line++;

		save = *line;
		*line = L'\0';

		if( (memo->ScrollBarPosition > pos) && ((height - memo->Height) > pos) )
		{
			TempPos++; 
		}
		else
		{
			// If height exceeds memo->Height 
			// Drawing alternative 14 lines in help frame.
			if( bScrollBar )
			{	
				if( (pos-TempPos) < memo->Height )
				{
					DrawStringJustifiedWithAttribute( memo->Left, memo->Left + memo->Width, memo->Top + (pos-TempPos),
						memo->Justify, text, memo->FGColor | memo->BGColor );
					
				}
			}
			// If No of Lines is less than Memo->Height
			// Drawing a string in a help frame
			else
			{
				memo->ScrollBarPosition = 0;
				DrawStringJustifiedWithAttribute( memo->Left, memo->Left + memo->Width, memo->Top + pos,
						memo->Justify, text, memo->FGColor | memo->BGColor );
			}
			
		}

		if ( ( *line = save ) != L'\0' )
		{
			line++;
			if ( ( *line == L'\r' ) || ( *line == L'\n' ) )
				line++;
		}
	}


	// Drawing Scrollbar For Help Frame.
	if( memo->ParentFrameType == HELP_FRAME )
	{
		// If scrollbar needed draw the scroll bar
		if( bScrollBar )
			StyleDrawHelpScrollBar(memo, height) ;
		else
			MemoEraseScrollBar(memo) ;	
	}

	if ( pos < height )
		height = pos;

	memo->DisplayLines = height;
	
	FlushLines( memo->Top, memo->Top + memo->Height -1 );
	if( ( memo->ParentFrameType == HELP_FRAME ) && ( bScrollBar ))
		DoRealFlushLines();
	MemFreePointer( (VOID **)&newText );

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoDrawScrollBar	
//
// Description:	Function to draw memo scrollbar
//
// Input:	MEMO_DATA *memo, UINT16 height
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemoDrawScrollBar( MEMO_DATA *memo, UINT16 height)
{
	#define VISIBLE_AREA_HEIGHT (memo->Height - 1)
	#define SCROLLBAR_AREA_HEIGHT (memo->Height)

	UINT16 pos=0 ;
	UINT32	FirstLine=0,LastLine=0,ScrollbarHeight = 0,j = 0;
	CHAR16	ArrUp[2]={{GEOMETRICSHAPE_UP_TRIANGLE},{0x0000}},ArrDown[2]={{GEOMETRICSHAPE_DOWN_TRIANGLE},{0x0000}},ScrlSel[2]={{BLOCKELEMENT_FULL_BLOCK/*L'N'*/},{0x0000}},ScrlNSel[2]={{BLOCKELEMENT_LIGHT_SHADE/*L'S'*/},{0x0000}};
		
	// Calculated scrollbar length based upon the height of the Lines.
	ScrollbarHeight = ( (SCROLLBAR_AREA_HEIGHT - 2) * VISIBLE_AREA_HEIGHT ) / height;
	
	// Calculated the First line of the scroll bar and last line of the scrollbar.		
	FirstLine = memo->ScrollBarPosition * ( (SCROLLBAR_AREA_HEIGHT - 2) - ScrollbarHeight ) / ( height - VISIBLE_AREA_HEIGHT ) + memo->Top + 1;
	
	LastLine  = FirstLine + ScrollbarHeight;

	for ( pos = 1,j = memo->Top; pos <= (UINT32)SCROLLBAR_AREA_HEIGHT ; pos++, j++ )
	{
		// Drawing Up Arrow
		if (pos == 1){
			    DrawStringWithAttribute( memo->Left + memo->Width , memo->Top, ArrUp, 
                                                StyleGetScrollBarUpArrowColor() );
		}
		// Drawing Down Arrow
                else if ( pos == (UINT32 )( SCROLLBAR_AREA_HEIGHT )){
                            DrawStringWithAttribute( memo->Left + memo->Width , memo->Top + (memo->Height-1), ArrDown, 
                                                 StyleGetScrollBarDownArrowColor() );	
		}
		// Drawing Scroll Bar(Scroll selector)
	        else if ( (j >= FirstLine) && (j <= LastLine) ){
		            DrawStringWithAttribute( memo->Left + memo->Width, j, ScrlSel, 
                                                 StyleGetScrollBarColor() );
		}
		// Drawing scroll Not Selector bar
                else{
			DrawStringWithAttribute( memo->Left + memo->Width, j, ScrlNSel, 
                                                 StyleGetScrollBarColor() );
		}
                       
	}
	
} 
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoEraseScrollBar	
//
// Description:	Function to erase memo scrollbar
//
// Input:	MEMO_DATA *memo
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemoEraseScrollBar( MEMO_DATA *memo)
{
	UINT16 pos=0 ;
	UINT32 j=0 ;
	
	for ( pos = 0,j = memo->Top; pos < memo->Height; pos++,j++ )
		DrawStringWithAttribute(  memo->Left + memo->Width, j , L" ", 
					memo->FGColor | memo->BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuHandleAction
//
// Description:	Function to set callback.
//
// Input:		MEMO_DATA *memo, ACTION_DATA *Data
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoHandleAction( MEMO_DATA *memo, ACTION_DATA *Data)
{
	//[EIP:19479]RB:<Add>
	// Handling action for help frame.

    CONTROL_ACTION Action;
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if (memo->Interval == 0)
			return Status;
		if ( --(memo->Interval) == 0 )
		{
			// initialize the interval
			memo->Interval = (UINT8)(memo->ControlData.ControlFlags.ControlRefresh);
			return EFI_SUCCESS;
		}
		else
			return Status;
	}

	if ( Data->Input.Type != ACTION_TYPE_KEY )
	   return EFI_UNSUPPORTED;

 	//Get Key       
	Action = MapControlKeysHook(Data->Input.Data.AmiKey);

	
    switch ( Action )
    {
        case ControlActionHelpPageDown:

	// Identify the help frame by identifying the height of the help frame
	if( memo->ParentFrameType == HELP_FRAME)
	{
		// Incrementing the ScrollBarPosition.
		memo->ScrollBarPosition++;
		// Based upon ScrollBarPosition drawing the Memo again.
		gMemo.Draw(memo);
	}
            break;

        case ControlActionHelpPageUp:
	if( memo->ParentFrameType == HELP_FRAME)
	{
		// Decrementing ScrollBarPosition
		if( memo->ScrollBarPosition != 0 )
			memo->ScrollBarPosition--;
		else
			memo->ScrollBarPosition = 0;
			gMemo.Draw(memo);
	}
            break;

	default:
	   Status = EFI_UNSUPPORTED;
    }


	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoSetCallback
//
// Description:	Function to set callback.
//
// Input:		MEMO_DATA *memo, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoSetCallback( MEMO_DATA *memo, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoSetFocus
//
// Description:	Function to set focus.
//
// Input:		MEMO_DATA *memo, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoSetFocus(MEMO_DATA *memo, BOOLEAN focus)
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoSetPosition
//
// Description:	Function to set position.
//
// Input:		MEMO_DATA *memo, UINT16 Left, UINT16 Top 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoSetPosition(MEMO_DATA *memo, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( memo, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		MEMO_DATA *memo, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoSetAttributes(MEMO_DATA *memo, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( memo, FGColor, BGColor );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		MEMO_DATA *memo, UINT16 width, UINT16 height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoSetDimensions( MEMO_DATA *memo, UINT16 width, UINT16 height )
{
	memo->Width = width;
	memo->Height = height;

	MemFreePointer( (VOID **)&memo->EmptyString );
	memo->EmptyString = EfiLibAllocateZeroPool( (width + 1) * sizeof(CHAR16) );
	if ( memo->EmptyString == NULL )
		return EFI_OUT_OF_RESOURCES;

	MemFillUINT16Buffer( memo->EmptyString, width, L' ' );
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoSetJustify
//
// Description:	Function to set justify.
//
// Input:		MEMO_DATA *memo, UINT8 justify
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoSetJustify( MEMO_DATA *memo, UINT8 justify )
{
	if ( justify <= JUSTIFY_MAX )
	{
		memo->Justify = justify;
		return EFI_SUCCESS;
	}

	return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemoGetControlHeight
//
// Description:	Function to get the memo text height.
//
// Input:	MEMO_DATA *memo, UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MemoGetControlHeight( MEMO_DATA *memo, VOID *frame, UINT16 *height )
{
	CHAR16 *text = NULL, *newText = NULL;

	if(frame != NULL)
	{ // Memo control from Frame
		memo->Width = ((FRAME_DATA*)frame)->FrameData.Width - (UINT8)gLabelLeftMargin - 2;
	}
	// else messagebox memo

	text = HiiGetString( memo->ControlData.ControlHandle,UefiGetTitleField( (VOID *)memo->ControlData.ControlPtr));

	if ( text == NULL )
		return EFI_OUT_OF_RESOURCES;

	// XXX: this wrapping code is probably not compatible with all languages
	newText = StringWrapText( text, memo->Width, height );
	if ( newText != text )
		MemFreePointer( (VOID **)&text );

	MemFreePointer( (VOID **)&newText );

	return EFI_SUCCESS;
}
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**       (C)Copyright 1985-2011, American Megatrends, Inc.     **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**    5555 Oakbrook Pkwy, Norcross, Suite 200, Georgia 30093   **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

