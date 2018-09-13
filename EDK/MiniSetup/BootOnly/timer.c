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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/timer.c $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:59a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/timer.c $
// 
// 4     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 3     6/23/09 6:56p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:13p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		timer.c
//
// Description:	This file contains code to handle the timer.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimerCreateTimer
//
// Description:	function to create a timer event and to set the timer
//
// Input:		EFI_EVENT *Event, EFI_EVENT_NOTIFY Callback,
//				VOID *Context, EFI_TIMER_DELAY Delay, UINT64 Trigger,
//				EFI_TPL CallBackTPL
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimerCreateTimer( EFI_EVENT *Event, EFI_EVENT_NOTIFY Callback,
		VOID *Context, EFI_TIMER_DELAY Delay, UINT64 Trigger, EFI_TPL CallBackTPL )
{
	EFI_STATUS Status;
	UINT32 EventType = EFI_EVENT_TIMER;

	if ( Callback != NULL )
		EventType |= EFI_EVENT_NOTIFY_SIGNAL;
	
	Status = gBS->CreateEvent(
			EventType,
			CallBackTPL,
			Callback,
			Context,
			Event
			);

	if ( EFI_ERROR( Status ) )
		return Status;

	Status = gBS->SetTimer( *Event, Delay, Trigger );
	if ( EFI_ERROR( Status ) )
		TimerStopTimer( Event );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimerStopTimer
//
// Description:	function to stop the timer event.
//
// Input:		EFI_EVENT *Event
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimerStopTimer( EFI_EVENT *Event )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( ( Event == NULL ) || ( *Event == NULL ) )
		return Status;

	gBS->CloseEvent( *Event );
	*Event = NULL;

	return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
