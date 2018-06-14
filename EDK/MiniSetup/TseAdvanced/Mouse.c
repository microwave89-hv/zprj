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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseAdvanced/Mouse.c $
//
// $Author: Premkumara $
//
// $Revision: 19 $
//
// $Date: 8/28/14 8:25a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseAdvanced/Mouse.c $
// 
// 19    8/28/14 8:25a Premkumara
// [TAG]	EIP103757
// [Category]	Improvement
// [Description]	- Introduced two functions such as
// TSE_SOFTKBD_GetMouseCoordinates() and TSE_SOFTKBD_GetButtonStatus()
// to override softkbd interface such as GetButtonStatus() and
// GetCoordinate(). 
// [Files]	Mouse.c
// 
// 18    8/28/14 6:04a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 17    5/02/14 9:23p Arunsb
// EIP164232 Error case handled properly
// 
// 16    5/02/14 7:03a Premkumara
// [TAG]  		EIP164232
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When password keyboard is launched and mouse pointer is
// placed on softkbd mouse will flickers continously.
// [RootCause]  	MouseRefresh and MouseStop is calling contiously in loop
// so mouse pointer get flickers
// [Solution]  	When mouse pointer is on softkbd and is static then stop
// calling MouseRefresh and MouseFreeze
// [Files]  		PopupPassword.c, CommonHelper.c, Mouse.c
// 
// 15    10/18/12 5:45a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 17    10/10/12 12:28p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 14    5/28/12 11:55a Premkumara
// [TAG]  		EIP89272
// [Category]  	Improvement
// [Description]  	Change softkbd layout for numeric control
// [Files]  		CommonHelper.c, Mouse.c, Minisetup.h, C, Numeric.c
// 
// 13    5/28/12 11:33a Premkumara
// [TAG]  		EIP88912
// [Category]  	Improvement
// [Description]  	On password window display the softkbd with only with
// valid key's
// [Files]  		CommonHelper.c, Postmgmtext.c, Mouse.c, PopupPassword.c
// 
// 12    5/09/12 4:09p Arunsb
// [TAG]  		EIP89753 
// [Category]  	Improvement
// [Description]  	Make mouse.c functions as board module hook
// [Files]  		Amitse.sdl and mouse.c
// 
// 11    4/05/12 7:11a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 10    4/04/12 12:38a Rajashakerg
// [TAG]  		EIP83753
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SoftKbd flickers when positioned near Top/Left end of the
// screen display.
// [RootCause]  	When Soft kbd is positioned near Top/Left end of the
// screen to display and when mouse pointer is on softkbd then we are
// stopping the mouse.
// Because of the implicit type casting of negative to UINT32 by the
// compiler the logic failed to stop the mouse when it is on softkbd.
// [Solution]  	 In the logic to stop the mouse on soft kbd the cordinates
// check is Explicitly type cast to INT32. 
// [Files]  		Mouse.c
// 
// 9     4/03/12 3:07a Premkumara
// [TAG]  		EIP84150
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	All the timers for mouse drivers before exiting from setup
// is not  stopped
// [RootCause]  	MouseDestroy() is not called StopPointingDevice()
// function to stop Mouse device
// [Solution]  	StopPointingDevice() function is called in MouseDestroy()
// function
// [Files]  		Mouse.c, Protocol.c, Ezport/StyleCommon.c,
// EzportPlus/StyleCommon.c, Legacy/StyleCommon.c, Minisetupext.c
// 
// 8     1/18/12 4:58a Rajashakerg
// [TAG]  		EIP79962 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse pointer corruption in GTSE
// [RootCause]  	For GTSE, the cordanites comparison logic went wrong for 
// stopping the mouse pointer when it is present while 
// updating the screen buffer.
// [Solution]  	Corrected the logic to stop the mouse when mouse pointer
//  is present on screen we are updating.
// [Files]  		buffer.c, CommonHelper.c, Mouse.c
// 
// 7     11/20/11 7:33a Rajashakerg
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
// 6     3/29/11 12:17p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 5     3/28/11 9:08p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 4     4/21/10 12:00p Madhans
// Tse 2.02
// 
// 2     2/26/10 8:46p Madhans
// For Tse 2.01.1204. Refer Changelog.log file change history
// 
// 11    2/23/10 8:33p Madhans
// For GTSE support.
// 
// 10    2/19/10 11:32a Madhans
// to avoid build errors
// 
// 9     2/19/10 8:06a Mallikarjunanv
// updated year in copyright message
// 
// 8     2/05/10 6:03p Madhans
// Mouse.c is moved to Binary to contol TSE_MOUSE_SUPPORT from binary
// 
// 5     9/03/09 2:45a Madhans
// updated file wiht the fix for eip 25555
// 
// 4     8/13/09 7:37a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 3     7/20/09 1:16p Mallikarjunanv
// updated the #if conditions
// 
// 2     6/12/09 7:43p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Mouse.c
//
// Description:	This file contains code to handle Mouse Operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//#include "minisetup.h"
#ifdef TSE_FOR_APTIO_4_50

#include "Token.h" 
#include <Efi.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/AMIPostMgr.h>
#include "TseCommon.h"
#include "commonoem.h"

#else //#ifdef TSE_FOR_APTIO_4_50

#include "minisetup.h"

#endif //#ifdef TSE_FOR_APTIO_4_50

#if TSE_STYLE_GTSE_BIN_SUPPORT
#include "gtseconfig.h"
#endif
 
#if MINISETUP_MOUSE_SUPPORT 

#if OLD_MOUSE_DRIVER_SUPPORT 
#include "Include\Protocol\MouseLib\MouseLib.h"
#else 
#include "Include\Protocol\MouseProtocol.h"
#endif 

#if AMITSE_SOFTKBD_SUPPORT
#include "Include\Protocol\SoftKbdProtocol.h"

SOFT_KBD_PROTOCOL *TSESoftKbd_n = NULL;
EFI_GUID gSoftKbdGuid = EFI_SOFT_KBD_PROTOCOL_GUID;
#endif 


#define CURSOR_WIDTH   20
#define CURSOR_HEIGHT  20

EFI_GUID gMouseDriverGuid = EFI_MOUSE_DRIVER_PROTOCOL_GUID;
DXE_MOUSE_PROTOCOL *TSEMouse = (DXE_MOUSE_PROTOCOL *)NULL;
DXE_MOUSE_PROTOCOL FakeTSEMouse;
INT32 Screen_Top=0,Screen_Left=0;		//Calculated Setup Screen Top and Left
EFI_STATUS GetScreenResolution(UINTN *ResX, UINTN *ResY);
UINTN HiiGetGlyphWidth(VOID);
UINTN HiiGetGlyphHeight(VOID);
UINTN StyleGetStdMaxRows(VOID);
extern UINTN gMaxRows;
extern UINTN gMaxCols;
extern UINTN gPostStatus;
VOID TSEStringReadLoopEntryHook(VOID);
VOID TSEStringReadLoopExitHook(VOID);
VOID TSEMouseInitHook(VOID);
VOID TSEMouseStopHook(VOID);
VOID TSEMouseRefreshHook(VOID);
VOID TSEMouseStartHook(VOID);
BOOLEAN TSEMouseIgnoreMouseActionHook(VOID);
VOID TSEMouseDestroyHook(VOID);

//EIP-103757 Starts
#if AMITSE_SOFTKBD_SUPPORT
//<AMI_PHDR_START>
//--------------------------------------------------------------------------------
// Procedure:	TSE_SOFTKBD_GetMouseCoordinates
//
// Description:	Function to return the mouse co-ordinates if it is over softkbd
//
// Input:		DXE_MOUSE_PROTOCOL *, INT32 *, INT32 *, INT32 *
//
// Output:		EFI_STATUS
//
//--------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSE_SOFTKBD_GetMouseCoordinates (DXE_MOUSE_PROTOCOL *This, INT32 *X, INT32 *Y, INT32 *Z)
{
    EFI_STATUS 	Status = EFI_UNSUPPORTED;
    UINT32 			x = 0, y = 0, z = 0;
    UINT32 			SoftKbdStartX = 0, SoftKbdStartY = 0, SoftKbdWidth = 0, SoftKbdHeight = 0;

    if (NULL == TSESoftKbd_n)
    {
        return Status;
    }

    if (TSESoftKbd_n->SoftKbdActive) //if softkbd active
    {
    	TSESoftKbd_n->GetPosition(TSESoftKbd_n,FALSE, &SoftKbdStartY,&SoftKbdStartX);
    	TSESoftKbd_n->GetDimension(TSESoftKbd_n,&SoftKbdWidth, &SoftKbdHeight);
    	TSEMouse->GetCoordinates(TSEMouse, &x, &y, &z);
        
        //Give the mouse co-ordinates only if the mouse is inside softkbd and when is not in dragging state
        if ( ( x > SoftKbdStartX) && (y > SoftKbdStartY) && (x < (SoftKbdStartX + SoftKbdWidth)) && (y < (SoftKbdStartY + SoftKbdHeight)))
        {
            *X = x;
            *Y = y;
            *Z = z;
            Status = EFI_SUCCESS;
        }
        else
        {//If the mouse pointer is outside the softkbd, send 0s
            *X = *Y = *Z = 0;
            Status = EFI_NOT_READY;
        }
    }
    return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------------
// Procedure:	TSE_SOFTKBD_GetButtonStatus
//
// Description:	Function to return the mouse button status if it is over softkbd
//
// Input:		DXE_MOUSE_PROTOCOL *, INT32 *
//
// Output:		EFI_STATUS
//
//--------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSE_SOFTKBD_GetButtonStatus (DXE_MOUSE_PROTOCOL *This, INT32 *ButtonStatus )
{
    EFI_STATUS 	Status = EFI_UNSUPPORTED;
    UINT32 			x = 0, y = 0, z = 0;
    UINT32 			SoftKbdStartX = 0, SoftKbdStartY = 0, SoftKbdWidth = 0, SoftKbdHeight = 0;

    if (NULL == TSESoftKbd_n)
    {
        return Status;
    }
    if (TSESoftKbd_n->SoftKbdActive)		//if softkbd active
    {
    	TSESoftKbd_n->GetPosition(TSESoftKbd_n,FALSE, &SoftKbdStartY,&SoftKbdStartX);
    	TSESoftKbd_n->GetDimension(TSESoftKbd_n,&SoftKbdWidth, &SoftKbdHeight);
    	TSEMouse->GetCoordinates(TSEMouse, &x, &y, &z);
	
        //Give the mouse co-ordinates only if the mouse is inside softkbd and when is not in dragging state
        if ( ( x > SoftKbdStartX) && (y > SoftKbdStartY) && (x < (SoftKbdStartX + SoftKbdWidth)) && (y < (SoftKbdStartY + SoftKbdHeight)) )
        {
        	TSEMouse->GetButtonStatus(TSEMouse, ButtonStatus);
			Status = EFI_SUCCESS;
        } 
        else
        {//If the mouse pointer is outside the softkbd, send NULL
            *ButtonStatus = TSEMOUSE_NULL_CLICK;
            Status = EFI_NOT_READY;
        }
    }
    return Status;
}
#endif			//end for #if AMITSE_SOFTKBD_SUPPORT
//EIP-103757 Ends

#if !OVERRIDE_TSEMouseInit
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseInit
//
// Description:	Function to initialize the mouse
//
// Input:		None 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemCopy( VOID *dest, VOID *src, UINTN size );
VOID TSEMouseInit(VOID)
{
	EFI_STATUS Status;
	UINTN HorizontalResolution = 0;
	UINTN VerticalResolution = 0;

	Status = gBS->LocateProtocol(&gMouseDriverGuid, NULL, &TSEMouse);
	if (EFI_ERROR (Status))
	{ 
	  TSEMouse=NULL;
	} 
	else 
	{
		//Initialize the Mouse to Full Screen Resolution in case of QuietBoot
		if(TSE_POST_STATUS_IN_QUITE_BOOT_SCREEN == gPostStatus)
 		{
			GetScreenResolution(&HorizontalResolution, &VerticalResolution);
			if (TSEMouse) 
			{
				//Initializing the Mouse (CURSOR,BOUNDARY,MAPPING etc)
	#if OLD_MOUSE_DRIVER_SUPPORT 
				TSEMouse->Initialize(
											(UINT32)0,
											(UINT32)0,
											(UINT32)HorizontalResolution,
											(UINT32)VerticalResolution
										);
	#else
				TSEMouse->InitializePointingDevice(
																TSEMouse,
																(UINT32)0,
																(UINT32)0,
																(UINT32)HorizontalResolution,
																(UINT32)VerticalResolution
															);
	#endif
			}
		}
		else
		{
			Status = GetScreenResolution(&HorizontalResolution, &VerticalResolution);	
			if ( EFI_ERROR( Status ) )
				TSEMouse = NULL;
	
			if(TSEMouse)
			{
	
	#if TSE_STYLE_GTSE_BIN_SUPPORT
				{
					GTSESetupConfigData* Data;
					Data = GTSEGetConfigData();
					Screen_Top =  Data->StartY ;
					Screen_Left = Data->StartX ;
				}
	#else
				Screen_Top = (INT32)(VerticalResolution - (gMaxRows*HiiGetGlyphHeight()) ) /2;
				Screen_Left = (INT32)(HorizontalResolution - (gMaxCols*HiiGetGlyphWidth()) ) /2;
	#endif
	
	#if OLD_MOUSE_DRIVER_SUPPORT 
				TSEMouse->Initialize(
							(UINT32)Screen_Left,
							(UINT32)Screen_Top,
							(UINT32)(Screen_Left + (gMaxCols*HiiGetGlyphWidth())),
							(UINT32)(Screen_Top + (gMaxRows*HiiGetGlyphHeight()))
							);
	#else
				//Initializing the Mouse (CURSOR,BOUNDARY,MAPPING etc)
				TSEMouse->InitializePointingDevice(TSEMouse,
							(INT32)Screen_Left,
							(INT32)Screen_Top,
							(INT32)(Screen_Left + (gMaxCols*HiiGetGlyphWidth())),
							(INT32)(Screen_Top + (gMaxRows*HiiGetGlyphHeight()))
							);
	#endif
			}
		}//End of gPostStatus not quietBoot case
#if AMITSE_SOFTKBD_SUPPORT
		if (TSEMouse)
		{
		  MemCopy (&FakeTSEMouse, TSEMouse, sizeof (DXE_MOUSE_PROTOCOL));
		  FakeTSEMouse.GetCoordinates = TSE_SOFTKBD_GetMouseCoordinates;
		  FakeTSEMouse.GetButtonStatus = TSE_SOFTKBD_GetButtonStatus;
	  
		  Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);
		  if (!EFI_ERROR (Status)){
			  TSESoftKbd_n->UpdateMouseInterface (TSESoftKbd_n, &FakeTSEMouse);
		  }
		}
#endif
	}
	TSEMouseInitHook();
}
#endif

#if !OVERRIDE_TSEMouseStop
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseStop
//
// Description:	Function to handle the mouse stop
//
// Input:		None 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEMouseStop(VOID)
{
    //Stop mouse pointer draw
    if(TSEMouse!=NULL)
    {
#if OLD_MOUSE_DRIVER_SUPPORT 
        TSEMouse->Stop();
#else
        TSEMouse->StopUpdatingMouseCursor(TSEMouse);
#endif
     }

    TSEMouseStopHook();
}
#endif

#if !OVERRIDE_TSEIsMouseClickedonSoftkbd
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIsMouseClickedonSoftkbd
//
// Description:	Function to handle the mouse Clicked on Softkbd
//
// Input:		None 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TSEIsMouseClickedonSoftkbd(VOID)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT32 x=0,y=0, z=0;
	UINT32 SoftKbdStartX=0, SoftKbdStartY=0, SoftKbdWidth=0, SoftKbdHeight=0;

#if AMITSE_SOFTKBD_SUPPORT
Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);

    	if( Status==( EFI_INVALID_PARAMETER | EFI_NOT_FOUND ) )
    	{ 
        	TSESoftKbd_n=NULL;
    	}
	
	TSEMouse->GetCoordinates(TSEMouse,&x,&y,&z);
	TSESoftKbd_n->GetPosition(TSESoftKbd_n, FALSE ,&SoftKbdStartY,&SoftKbdStartX);
	TSESoftKbd_n->GetDimension(TSESoftKbd_n,&SoftKbdWidth, &SoftKbdHeight);
	//EIP 83753 : SoftKbd flickers when positioned near Top/Left end of the screen display. 
     if((( (INT32)x > (INT32)(SoftKbdStartX-HiiGetGlyphHeight()))&&((INT32)y > (INT32)(SoftKbdStartY-(2*HiiGetGlyphHeight()))))&& (((INT32)x < (INT32)(SoftKbdStartX+SoftKbdWidth))&&((INT32)y < (INT32)(SoftKbdStartY + SoftKbdHeight))) )
		return TRUE;
	else
		return FALSE;
#endif
return FALSE;
}
#endif

#if !OVERRIDE_TSEMouseRefresh
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseRefresh
//
// Description:	Function to handle the mouse Refresh
//
// Input:		None 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEMouseRefresh(VOID)
{
	 EFI_STATUS Status = EFI_UNSUPPORTED;

 	if((TRUE == TSEMouseIgnoreMouseActionHook())&&(TRUE == TSEIsMouseClickedonSoftkbd()))
	{
		TSEMouse->StopUpdatingMouseCursor(TSEMouse);
	}

	TSEMouseRefreshHook();

    //refresh mouse pointer
    if(TSEMouse!=NULL)
    {
#if OLD_MOUSE_DRIVER_SUPPORT 
        TSEMouse->Refresh();
#else
	TSEMouse->UpdateMousePointerProperty(TSEMouse ,MOUSE_POINTER_PROPERTY_NORMAL);
        TSEMouse->RefreshMouseCursor(TSEMouse);
#endif
    }
}
#endif

#if !OVERRIDE_TSEMouseStart
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseStart
//
// Description:	Function to handle the mouse Startd
//
// Input:		None 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEMouseStart(VOID)
{
    TSEMouseStartHook();

	if(TSEMouse!=NULL)
#if OLD_MOUSE_DRIVER_SUPPORT 
		TSEMouse->Start();
#else
        TSEMouse->StartUpdatingMouseCursor(TSEMouse);
#endif
}
#endif

#if !OVERRIDE_TSEMouseFreeze
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseFreeze
//
// Description:	Function to handle the mouse Destory
//
// Input:		None 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEMouseFreeze(VOID)
{
    //Stop mouse pointer draw
    if(TSEMouse!=NULL)
#if OLD_MOUSE_DRIVER_SUPPORT 
        return;
#else
        TSEMouse->UpdateMousePointerProperty(TSEMouse ,MOUSE_POINTER_PROPERTY_FREEZE);
#endif

}
#endif

#if !OVERRIDE_TSEGetCoordinates
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEGetCoordinates
//
// Description:	Function to handle the mouse Destory
//
// Input:		None 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEGetCoordinates(INT32 *x, INT32 *y, INT32 *z)
{
EFI_STATUS Status = EFI_SUCCESS;
    //Stop mouse pointer draw
    if(TSEMouse!=NULL)
#if OLD_MOUSE_DRIVER_SUPPORT 
        return;
#else
        TSEMouse->GetCoordinates(TSEMouse ,x,y,z);
#endif
   return EFI_SUCCESS;	
}
#endif

#if !OVERRIDE_TSEMouseReadInfo
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseReadInfo
//
// Description:	Function to read the information using mouse
//
// Input:		MOUSE_INFO *MouseInfo 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseReadInfo(MOUSE_INFO *MouseInfo)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT32 Button_Status=0;
    UINT32 x=0,y=0, z=0;
    UINT32 SoftKbdStartX=0, SoftKbdStartY=0, SoftKbdWidth=0, SoftKbdHeight=0;

    if(NULL == TSEMouse)
        return EFI_UNSUPPORTED;

    TSEMouse->GetCoordinates(TSEMouse,&x,&y,&z);

    // If mouse action are consumed by Modules like SoftKeyBoard.
    if(TSEMouseIgnoreMouseActionHook() == TRUE)
    {

#if AMITSE_SOFTKBD_SUPPORT
 	Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);

    	if( Status==( EFI_INVALID_PARAMETER | EFI_NOT_FOUND ) )
    	{ 
        	TSESoftKbd_n=NULL;
    	}
	
	TSESoftKbd_n->GetPosition(TSESoftKbd_n,FALSE, &SoftKbdStartY,&SoftKbdStartX);
	TSESoftKbd_n->GetDimension(TSESoftKbd_n,&SoftKbdWidth, &SoftKbdHeight);
	if((( x > SoftKbdStartX)&&(y > SoftKbdStartY))&& ((x < (SoftKbdStartX+SoftKbdWidth))&&(y <(SoftKbdStartY + SoftKbdHeight))) )
	{
	//TSESoftKbd_n->UpdateMouseInterface(TSESoftKbd_n, TSEMouse);
	
		return EFI_NOT_FOUND;
	}
		//  else
		//	TSESoftKbd_n->UpdateMouseInterface(TSESoftKbd_n, NULL);
#endif

	       // return EFI_NOT_FOUND;
    }
#if OLD_MOUSE_DRIVER_SUPPORT 
    //Getting Mouse Button Status
    TSEMouse->GetButtonStatus(&Button_Status);     

    //Getting Mouse Pointer Position
    TSEMouse->GetPosition((INT32*)&x,(INT32*)&y);    
#else
   
   TSEMouse->MousePoll(TSEMouse);
   TSEMouse->GetButtonStatus(TSEMouse,&Button_Status);     

    //Getting Mouse Pointer Position
    TSEMouse->GetCoordinates(TSEMouse,&x,&y,&z);    
#endif

    y-=Screen_Top;
    x-=Screen_Left;

    //Converting Graphics Resolution to Text Mode Location
    MouseInfo->Left = (UINT16)(x/HiiGetGlyphWidth());
    MouseInfo->Top = (UINT16)(y/HiiGetGlyphHeight());

    //Setting the Calculated SCREEN_TOP and SCREEN_LEFT Rather than Hardcoding
//    MouseInfo->Top-=Screen_Top;
//    MouseInfo->Left-=Screen_Left;
    MouseInfo->ButtonStatus=Button_Status;

    return EFI_SUCCESS;		
}
#endif

#if !OVERRIDE_TSEMouseDestroy
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseDestroy
//
// Description:	Function to handle the mouse Destory
//
// Input:		None 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEMouseDestroy(VOID)
{
    //Stop mouse pointer draw
	if(TSEMouse!=NULL)
	{
#if OLD_MOUSE_DRIVER_SUPPORT 
		TSEMouse->Stop();
#else	
		TSEMouse->StopUpdatingMouseCursor(TSEMouse);
		TSEMouse->StopPointingDevice(TSEMouse);	//EIP-84150 
#endif
	}

    TSEMouseDestroyHook();
}
#endif

#if !OVERRIDE_TSEGetactualScreentop
//EIP 79962 : START
// Mouse pointer corruption in GTSE  
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEGetactualScreentop
//
// Description:	Function to retrun the actual Screen Top value
//
// Input:		None 
//
// Output:		INT32
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT32 TSEGetactualScreentop(VOID)
{
	return Screen_Top;
}
//EIP 79962 : END
#endif

#if AMITSE_SOFTKBD_SUPPORT
#if !OVERRIDE_TSENumericSoftKbdInit
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSENumericSoftKbdInit
//
// Description:	Function to display the numeric softkbd
//
// Input:		None 
//
// Output:		INT32
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSENumericSoftKbdInit(VOID)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);

   	if( Status==( EFI_INVALID_PARAMETER | EFI_NOT_FOUND ) )
   	{ 
       	TSESoftKbd_n=NULL;
   	}
	if(NULL == TSESoftKbd_n)
	 return;
	
	TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_NUMERIC);
	TSEStringReadLoopEntryHook();		
}
#endif

#if !OVERRIDE_TSENumericSoftKbdExit
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSENumericSoftKbdExit
//
// Description:	Function to destroy the numeric softkbd display
//
// Input:		None 
//
// Output:		INT32
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSENumericSoftKbdExit (VOID)
{
	if(NULL == TSESoftKbd_n)
	 return;
	TSEStringReadLoopExitHook();
	TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_FULL_US_KEYBOARD);
}
#endif

//EIP-88912 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSESetPwdKeyboardLayout
//
// Description:	function to initialize TSESetKeyboardLayout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSESetPwdKeyboardLayout(VOID)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);

	if(EFI_ERROR( Status ))
	{ 
		TSESoftKbd_n=NULL;
	}
	if(NULL == TSESoftKbd_n)
	 return;

	if ( SETUP_STORE_KEYCODE_PASSWORD )
		TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_FULL_US_KEYBOARD );
	else
		TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_PRINTABLE_KEYS );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEResetPwdKeyboardLayout
//
// Description:	function to exit TSEResetKeyboardLayout and reset with default keyboard layout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEResetPwdKeyboardLayout(VOID)
{
	if(NULL == TSESoftKbd_n)
	 return;
	TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_FULL_US_KEYBOARD);
}
//EIP-88912 Ends

//EIP-89272 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEPrintableKeysSoftKbdInit
//
// Description:	function to launch PrintableKeysSoftkbd layout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEPrintableKeysSoftKbdInit(VOID)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);

	if(EFI_ERROR( Status ))
	{ 
		TSESoftKbd_n=NULL;
	}
	if(NULL == TSESoftKbd_n)
	 return;
	
	TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_PRINTABLE_KEYS);
	TSEStringReadLoopEntryHook();		
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEPrintableKeysSoftKbdExit
//
// Description:	function to exit PrintableKeysSoftkbd layout and reset with default keyboard layout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEPrintableKeysSoftKbdExit(VOID)
{
	if(NULL == TSESoftKbd_n)
	 return;
	TSEStringReadLoopExitHook();
	TSESoftKbd_n->SetKbdLayout(TSESoftKbd_n, SOFT_KEY_LAYOUT_FULL_US_KEYBOARD);
}

//EIP-89272 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    	TSEIsMouseOnSoftkbd
//
// Description:    	Function to return whether MousePointer is on softkbd or not
//
// Input:        	None 
//
// Output:        	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
TSEIsMouseOnSoftkbd(VOID)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    INT32 mouseX = 0, mouseY = 0, mouseZ = 0;
    INT32 SoftKbdStartX = 0, SoftKbdStartY = 0, SoftKbdWidth = 0, SoftKbdHeight = 0;
    INT32 SoftKbdPosX1 = 0, SoftKbdPosY1 = 0, SoftKbdPosX2 = 0, SoftKbdPosY2 = 0;

#if AMITSE_SOFTKBD_SUPPORT
    Status = gBS->LocateProtocol(&gSoftKbdGuid, NULL, &TSESoftKbd_n);

    if(EFI_ERROR( Status )) { 
      TSESoftKbd_n=NULL;
      return FALSE;
    }
    
    TSEMouse->GetCoordinates(TSEMouse,&mouseX, &mouseY, &mouseZ);
    TSESoftKbd_n->GetPosition(TSESoftKbd_n, FALSE , &SoftKbdStartY, &SoftKbdStartX);
    TSESoftKbd_n->GetDimension(TSESoftKbd_n, &SoftKbdWidth, &SoftKbdHeight);
    
    SoftKbdPosX1 = SoftKbdStartX - (INT32)HiiGetGlyphHeight();
    SoftKbdPosY1 = SoftKbdStartY - (INT32)HiiGetGlyphHeight();
    SoftKbdPosX2 = SoftKbdStartX + SoftKbdWidth;
    SoftKbdPosY2 = SoftKbdStartY + SoftKbdHeight;

    if( ( (mouseX > (INT32)(SoftKbdStartX-HiiGetGlyphHeight()))&& (mouseY > (INT32)(SoftKbdStartY-(HiiGetGlyphHeight()))))&&
        ( (mouseX < (INT32)(SoftKbdStartX+SoftKbdWidth))&& (mouseY < (INT32)(SoftKbdStartY + SoftKbdHeight)) )
      ) 
    {
        return TRUE;
    }
    else 
    {
        return FALSE;
    }
#endif
return FALSE;
}

#endif //AMITSE_SOFTKBD_SUPPORT
#endif //MINISETUP_MOUSE_SUPPORT

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
