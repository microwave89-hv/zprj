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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/postmgmt.c $
//
// $Author: Premkumara $
//
// $Revision: 38 $
//
// $Date: 8/28/14 8:38a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/postmgmt.c $
// 
// 38    8/28/14 8:38a Premkumara
// [TAG]       	EIP142551
// [Category]  	Bug Fix
// [Severity]		Minor
// [Symptom]		Mouse Movement is not initialized to Full Screen Resolution
// in case of quiet boot mode with high resolution OEM Logo.
// [Root Cause]	Mouse Initialization was not across the full screen incase
// of High Resolution Quiet Boot Logo.
// [Solution]		Initialised the Mouse with the Resolution Set in case of
// Quiet Boot logo so that Mouse will move acroos the Whole screen
// [Files]        Mouse.c, BootFlowLib.c, PostMgmt.c, PostMgmtExt.c,
// Notify.c, MinisetupExt.c
// 
// 37    8/28/14 7:29a Premkumara
// [TAG]		EIP107833, 125388
// [Category]	Improvement
// [Symptom:]	Setting best text and GOP mode while using TSEPostinterfaces
// before TSE or after TSE.
// [Files]		Protocol.c, AMITSE.sdl, CommonHelper.c, MiniSetup.sdl,
// PostMgmtc, PostmgmtExt.c, MessagBox.c
// 
// 36    8/28/14 5:52a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 35    5/02/14 12:51a Arunsb
// [TAG]	EIP148122
// [Category]	Improvement
// [Description]	INTN to UINTN for CordinateX and CordinateY variable in
// InitPostScreen to avoid negative condition
// [Files]	postmgmt.c
// 
// 34    2/11/14 9:30p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 33    2/11/14 8:08p Arunsb
// [TAG]  		EIP126104
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Calling SwitchToPostScreen after selecting option from BBS
// draws PostScreen and display post messages.
// [RootCause]  	When switchToPostscreen is called BBS menu is d
// [Solution]  	Drawing postscreen image and display post messages before
// BBS
// [Files]  		Postmgmt.c
// 
// 32    1/29/14 5:43p Arunsb
// [TAG]	EIP148122
// [Category]	Improvement
// [Description]	INTN to UINTN for CordinateX and CordinateY variable in
// InitPostScreen to avoid negative condition
// [Files]	postmgmt.c
// 
// 31    5/21/13 12:32p Arunsb
// [TAG]  		EIP124369
// [Category]  	Bug Fix
// [Solution]  	BGRT table header revision revised to 1 as per ACPI spec
// 5.0
// [Files]  		postmgmt.c
// 
// 30    5/12/13 8:35a Arunsb
// [TAG]  		EIP122277
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System halted when 4GB memory installed with Quiet Boot
// enabled in 32 bit platform
// [RootCause]  	Type casting problem
// [Solution]  	Type casted properly with UINTN for UINT64 member
// [Files]  		postmgmt.c
// 
// 29    4/17/13 1:13a Arunsb
// [TAG]  		EIP121116 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AMI small logo has damage on POST and boot
// [RootCause]  	When system starts with higher text resolution more than
// 100*31 then TSE not setting proper text mode
// [Solution]  	Mode set properly
// [Files]  		notify.c and postmgmt.c
// 
// 28    10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 26    9/25/12 12:39p Arunsb
// [TAG]  		EIP100558
// [Category]  	New Feature
// [Description]  	Provide solution to display the small logo in (0,0)
// graphics position
// [Files]  		postmgmt.c
// 
// 25    9/17/12 6:10a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 23    9/08/12 6:40p Arunsb
// [TAG]  		EIP100558
// [Category]  	New Feature
// [Description]  	Provide solution to display the small logo in (0,0)
// graphics position
// [Files]  		AMITSE.sdl, commonhelper.c, postmgmt.c and boot.c
// 
// 22    8/29/12 4:24p Arunsb
// [TAG]  			EIP94702
// [Description]  	Support for Native Resolution in POST/BOOT
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c, boot.c, logo.c,
// notify.c, postmgmt.c, tselite\minisetupext.c, ezport/stylecommon.c,
// ezportplus/stylecommon.c andlegacy/stylecommon.c
// 
// 21    5/29/12 7:02a Arunsb
// Commented for build error
// 
// 20    5/29/12 4:33a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 19    2/04/12 9:06a Premkumara
// Moved DrawOEMImage with some modification from binary to source
// 
// 18    1/31/12 1:22p Premkumara
// [TAG]  		EIP75136 
// [Category]  	New Feature
// [Description]  	Generic support for logos in RomHoles
// [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h,
// Postmgmt.c, AMILogo.h
// 
// 17    1/31/12 6:44a Arunsb
// [TAG]  		EIP81830
// [Category]  	Improvement
// [Description]  	Support to uninstall the BGRT on legacy boot.
// [Files]  		Commonhelper.c, postmgmt.c and boot.c
// 
// 16    11/21/11 8:37a Rajashakerg
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
// 15    11/20/11 7:15a Rajashakerg
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
// 14    6/29/11 10:16a Arunsb
// [TAG]           EIP58954
// [Category]      Improvement
// [Description]   Support for BGRT spec. version 1.2.
//                 ImageType field added in BGRT_TABLE to represent the
// type of image.
// [Files]         bootonly\logo.c and postmgmt.c
// 
// 13    6/04/11 1:52p Arunsb
// [TAG]             EIP58954
// [Category]      New Feature
// [Description]   Wrapper function added for InvalidateStatusInBgrt
// function.
// [Files]             Postmgmt.c, boot.c, logo.c commonoem.c and
//                       commonhelper.c
// 
// 12    5/29/11 12:09p Arunsb
// [TAG]           EIP58954
// [Category]      New Feature
// [Description]   Quiet boot logo's only added for BGRT. BGRT status
// field cleared if any changes happened in screen other than displaying
// the image.
// [Files]         Postmgmt.c, boot.c, logo.c commonoem.c and
// commonhelper.c
// 
// 11    5/04/11 5:09p Arunsb
// [TAG]           EIP58954
// [Category]      New Feature
// [Description]   Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added. Wrapper function
// ContribBGRTTableToAcpi added.
// [Files]         Postmgmt.c, commonoem.c,logo.c and commonhelper.c
// 
// 10    5/03/11 9:54p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added. EDK Build support added.
// [Files]  		Postmgmt.c, commonoem.c and commonhelper.c
// 
// 9     5/02/11 3:29p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added. EDK Build support added.
// [Files]  		Postmgmt.c, commonoem.c and commonhelper.c
// 
// 8     4/23/11 3:18p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added.
// [Files]  		Postmgmt.c, commonoem.c and commonhelper.c
// 
// 7     3/28/11 9:23p Madhans
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
// 6     1/06/11 1:55a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Calls to PostManagerProtocol->SwitchToPostScreen() after
// legacy option ROM execution cause CPU exception.
// [RootCause]  	After the notification, if the graphics driver
// uninstalled and reinstalled from core module then gGOP is getting
// corrupted.
// [Solution]  	Updated the files, by making gGOP/gUgaDraw to NULL in the
// update function and in switch to posty screen returining status as
// aborted if the gGOP/gUgaDraw is NULL
// [Files]  		protocol.c,notify.c,postmgmt.c
// 
// 5     12/29/10 2:31a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Calls to PostManagerProtocol->SwitchToPostScreen() after
// legacy option ROM execution cause CPU exception.
// [RootCause]  	After the notification, if the graphics driver
// uninstalled and reinstalled from core module then gGOP getting
// corrupted.
// [Solution]  	Updated gGop/UgaDraw before using it in AMITSE. 
// [Files]  		logo.c,minisetup.h, notify.c, postmgmt.c ,protocol.c
// 
// 3     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 4     2/04/10 11:21p Madhans
// To remove ConsoleControl dependance.
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
// 2     5/13/09 11:01a Madhans
// Signal the event once we create the timer. to read any pending keys
// 
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 5     3/31/09 4:00p Madhans
// 
// 4     2/05/09 5:19p Madhans
// PostMgrStatus interface added.
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
// Name:		postmgmt.c
//
// Description:	file to handle the post management operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#if !TSE_USE_EDK_LIBRARY
#include "Acpi.h" 
#include <Protocol\AcpiSupport.h>
#else
#include EFI_PROTOCOL_DEFINITION (AcpiTable)
#endif

#pragma pack (1)
typedef struct					//Structure for forming BGRT Table
{
	UINT16  Version;
	UINT8   Status;
	UINT8   ImageType;
	UINT64  ImageAddress;
	UINT32  ImageOffsetX;
	UINT32  ImageOffsetY;
}BGRT_TABLE;
#pragma pack()
#if !TSE_USE_EDK_LIBRARY
#define EFI_SIGNATURE_16(A,B)     ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D) (EFI_SIGNATURE_16 (A,B) | (EFI_SIGNATURE_16 (C,D) << 16))
#endif
#define BGRT_SIGNATURE             EFI_SIGNATURE_32 ('B','G','R','T')
VOID    FormBGRTTable (VOID **, UINTN *, UINT8 *, INTN, INTN, BOOLEAN);
UINT8   CalculateChecksum (VOID *, UINT8);
#define CREATOR_ID_AMI 0x20494D41
#define	CREATOR_REV_MS 0x00010013
UINT8   *GetACPIOEMID (VOID);
UINT8   *GetACPIOEMTableID (VOID);
UINT32  GetACPIOEMRevision (VOID);
LOGO_TYPE GetLogoType(UINT8 *ImageData);
LOGO_TYPE GetExtendedLogoType(UINT8 *ImageData);
VOID    *gBgrtSafeBuffer = NULL;		//EIP 58954 For BGRT table support
UINTN   gTableKey = 0; 
VOID 	InvalidateStatusInBgrtWrapper (VOID);
//EIP-75136 ROMHole Support
BOOLEAN IsOEMPOSTLogoSupport();
//EIP-75136 End
BOOLEAN 	IsMouseSupported(VOID);
BOOLEAN 	IsSoftKbdSupported(VOID);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawOEMImage
//
// Description:	Function to draw OEMLogo to in post screen operations
//
// Input:		UINTN *, UINTN*, INTN, INTN
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DrawOEMImage (UINTN *width, UINTN *height, INTN CoordinateX, INTN CoordinateY)
{
	EFI_GUID OEMLogoGuid = AMI_OEM_LOGO_GUID;
	UINT8 *ImageData = NULL;
	UINTN ImageSize = 0;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINTN       LogoType = 0;

	Status =  GetGraphicsBitMapFromFV( &OEMLogoGuid, &ImageData, &ImageSize );
	if(EFI_SUCCESS == Status)
	{
		DrawImage( ImageData, ImageSize, CA_AttributeRightTop, CoordinateX, CoordinateY, FALSE, width, height );
		LogoType = GetExtendedLogoType (ImageData);
		if (GIF_Logo != LogoType)
		{
			MemFreePointer ((VOID **)&ImageData);
		}            
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitPostScreen
//
// Description:	fucntion to perform the post screen operations
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DrawPostLogoAt0Pos (VOID);
VOID InitPostScreen( VOID )
{
	UINTN height, width, OrgHeight = 0;
    UINT8 *ImageData = NULL;
    UINTN ImageSize = 0;
	UINTN CoordinateX = 0;
	UINTN CoordinateY = 0;
	UINT32 HorizontalResolution = 0;
	UINT32 VerticalResolution = 0;
	UINTN ConCols = 0, ConRows = 0;
#if !SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	UINT32 ColorDepth;
	UINT32 RefreshRate;
#endif
	EFI_SIMPLE_TEXT_OUT_PROTOCOL *pConOut = gST->ConOut;
    UINTN       LogoType = 0;
	UINTN tempPostStatus;

	if ( pConOut == NULL )
		return;

	//If any SwitchToPostScreen happens during ProceedToBoot then taking backup of original gPostStatus before changing to IN_POST_SCREEN
	if (TSE_POST_STATUS_PROCEED_TO_BOOT == gPostStatus)
		tempPostStatus = gPostStatus;

	if ( gPostStatus <= TSE_POST_STATUS_IN_TSE ) //EIP-126104
		 gPostStatus = TSE_POST_STATUS_IN_POST_SCREEN;

#ifndef STANDALONE_APPLICATION
	if(gConsoleControl != NULL)
    gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
#endif

#if !APTIO_4_00
	SetDesiredTextMode ();
#else
	//  In Aptio use the Text mode as is it in post screen
	if (EFI_ERROR (gST->ConOut->QueryMode (gST->ConOut, gST->ConOut->Mode->Mode, &ConCols, &ConRows)))
	{
		gMaxRows = StyleGetStdMaxRows(); 
		gMaxCols = StyleGetStdMaxCols(); 
	}
	else if ((gMaxRows < ConRows) && (gMaxCols < ConCols))
	{
		SetDesiredTextMode ();
	}
#endif
	if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
		MouseInit();
	pConOut->EnableCursor( pConOut, FALSE );
	pConOut->SetAttribute( pConOut, EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
	pConOut->ClearScreen( pConOut );

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	if(gGOP)
	{
		HorizontalResolution = gGOP->Mode->Info->HorizontalResolution;
		VerticalResolution = gGOP->Mode->Info->VerticalResolution;
	}
#else
	if ( gUgaDraw != NULL )
	{
		gUgaDraw->GetMode (gUgaDraw, &HorizontalResolution, &VerticalResolution, &ColorDepth, &RefreshRate);
	}
#endif

	if ( gPostStatus > TSE_POST_STATUS_IN_TSE ) //EIP-126104
	{
		 InvalidateStatusInBgrtWrapper ();
		 return;
	}

	height = 0;

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	if(gGOP )
#else
	if ( gUgaDraw )
#endif
	{
		if (!DrawPostLogoAt0Pos ())
		{
			CoordinateX = (HorizontalResolution - (gMaxCols * HiiGetGlyphWidth ())) / 2;
			CoordinateY = (VerticalResolution - (gMaxRows * HiiGetGlyphHeight ())) / 2;
		}
		//EIP-75136 To display AMILogo on TopLeft corner of setup
	    if(EFI_SUCCESS == GetGraphicsBitMapFromFV( &gAMIEfiLogoGuid, &ImageData, &ImageSize ))
	    {
			
			MouseStop();//EIP 62763: Mouse stopped before drawing the post image.
			
	        DrawImage(
	            ImageData,
	            ImageSize,
	            CA_AttributeLeftTop,
	            CoordinateX,
	            CoordinateY,
	            FALSE,
	            &width,
	            &height
	            );
			 OrgHeight = height; 
          LogoType = GetExtendedLogoType (ImageData);
          if (GIF_Logo != LogoType)
          {
              MemFreePointer ((VOID **)&ImageData);
          }
			InvalidateStatusInBgrtWrapper ();
	    }
		//EIP-75136 To display OEM_POST_Logo on RightTop corner of setup 
		if (IsOEMPOSTLogoSupport())
		{
			if(EFI_SUCCESS == DrawOEMImage(&width, &height, CoordinateX, CoordinateY))
			{								
				InvalidateStatusInBgrtWrapper ();
			}
		}
		if (DrawPostLogoAt0Pos ())
		{
			if (height > (VerticalResolution - (gMaxRows * HiiGetGlyphHeight())) / 2)		//If height is lesser than empty space then make height as 0. Occurs for greater graphics resolution with lesser text resolution. 
			{
				height -= (VerticalResolution - (gMaxRows * HiiGetGlyphHeight())) / 2;
			}
		}
		height = (height / HiiGetGlyphHeight());
		if(OrgHeight % HiiGetGlyphHeight())			//Seeing remainder for original height
		    height ++;
	}

	//If SwitchToPostScreen is called during TSE_POST_STATUS_PROCEED_TO_BOOT poststatus then we need to save PROCEED_TO_BOOT to set it back after drawing postlogo to avoid drawing msgbox, message, other postinterfaces
	if (TSE_POST_STATUS_PROCEED_TO_BOOT == tempPostStatus)
		gPostStatus = TSE_POST_STATUS_PROCEED_TO_BOOT;

	DisplayActivePostMsgs(height);
    
    AfterInitPostScreenHook();
	MouseRefresh();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InstallKeyHandlers
//
// Description:	fucntion to install the timer event
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InstallKeyHandlers( VOID )
{
	EFI_STATUS Status;
	if(gKeyTimer != NULL)
		return; // timer already created.
	Status = TimerCreateTimer( &gKeyTimer, CheckForKeyHook, NULL, TimerPeriodic, TIMER_HALF_SECOND, EFI_TPL_CALLBACK );
	// Signal it once immediately.
    if (!EFI_ERROR(Status))
		gBS->SignalEvent( gKeyTimer );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InstallClickHandlers
//
// Description:	fucntion to install the timer event
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InstallClickHandlers( VOID )
{
	EFI_STATUS Status;
	if(gClickTimer != NULL)
		return; // timer already created.
	Status = TimerCreateTimer( &gClickTimer, CheckForClickHook, NULL, TimerPeriodic, TIMER_HALF_SECOND, EFI_TPL_CALLBACK );
	// Signal it once immediately.
    if (!EFI_ERROR(Status))
		gBS->SignalEvent( gClickTimer );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FormBGRTTable
//
// Description:	Created the BGRT table with the input params
//
// Input:		VOID * = Buffer to store the ACPI table
//				UINTN * = To store the size of the ACPI + BGRT table
//				UINT8 * = Address of the image to be to stored
//			 	INTN = X coordinate of the image 
//				INTN = Y coordinate of the image
//				BOOLEAN = Indicates whether to set the BGRT status field or not.
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FormBGRTTable (VOID **AcpiTableBuffer, UINTN *AcpiTableBufferSize, UINT8 *ImageAddress, INTN ImageXOffset, INTN ImageYOffset, BOOLEAN GifImagePresence)
{
    BGRT_TABLE  BgrtTable = {0};
    const UINT8 *OemId  = GetACPIOEMID ();
    const UINT8 *OemTblId = GetACPIOEMTableID ();
    UINT8       iIndex = 0;
    UINT8       Checksum = 0;
    UINT8       AcpiHdrSize = 0;          
#if TSE_USE_EDK_LIBRARY
    EFI_ACPI_DESCRIPTION_HEADER AcpiHdr = {0};
    AcpiHdrSize = sizeof (EFI_ACPI_DESCRIPTION_HEADER);
#else
    ACPI_HDR    AcpiHdr = {0};
    AcpiHdrSize = sizeof (ACPI_HDR);
#endif
    AcpiHdr.Signature = BGRT_SIGNATURE;
    AcpiHdr.Length = AcpiHdrSize + sizeof(BGRT_TABLE);
    AcpiHdr.Revision = 1;
    AcpiHdr.Checksum = 0;
    AcpiHdr.CreatorId = CREATOR_ID_AMI; //"AMI"
    for (iIndex = 0; ((iIndex < 6) && (OemId [iIndex])); iIndex ++)
    {
        AcpiHdr.OemId [iIndex] = OemId [iIndex];
    }
#if TSE_USE_EDK_LIBRARY
    AcpiHdr.OemRevision = GetACPIOEMRevision ();
    AcpiHdr.CreatorRevision = CREATOR_REV_MS;
    for (iIndex = 0; ((iIndex < 8) && (OemTblId [iIndex])); iIndex ++)
    {
        ((UINT8 *)(&AcpiHdr.OemTableId)) [iIndex] = OemTblId [iIndex];
    }
#else
    AcpiHdr.OemRev = GetACPIOEMRevision ();
    AcpiHdr.CreatorRev = CREATOR_REV_MS;    
    for (iIndex = 0; ((iIndex < 8) && (OemTblId [iIndex])); iIndex ++)
    {
        AcpiHdr.OemTblId [iIndex] = OemTblId [iIndex];
    }
#endif
	BgrtTable.Version = 1;
	if (!GifImagePresence)			//If gif image presented then status field should be 0.
	{
		BgrtTable.Status = 1;
	}
    BgrtTable.ImageType = 0;					//0 Represents BMP image
	BgrtTable.ImageAddress = (UINTN)ImageAddress;
    BgrtTable.ImageOffsetX = (UINT32)ImageXOffset;
    BgrtTable.ImageOffsetY = (UINT32)ImageYOffset;

    Checksum = CalculateChecksum (&AcpiHdr, AcpiHdrSize);
    Checksum += CalculateChecksum (&BgrtTable, (UINT8)sizeof (BGRT_TABLE));
    AcpiHdr.Checksum = Checksum;

    *AcpiTableBuffer = EfiLibAllocatePool (AcpiHdrSize + sizeof (BGRT_TABLE));
    if (NULL == *AcpiTableBuffer)
    {
        return;
    }
    EfiCopyMem (*AcpiTableBuffer, &AcpiHdr, AcpiHdrSize);
    EfiCopyMem (((UINT8 *)(*AcpiTableBuffer)) + AcpiHdrSize, &BgrtTable, sizeof (BGRT_TABLE));    
    *AcpiTableBufferSize = AcpiHdrSize + sizeof(BGRT_TABLE);     
}	

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AddImageDetailToACPI
//
// Description:	Adds the image data to the ACPI Table.
//
// Input:		UINT8 * = Address of the image to be to stored
//			 	INTN = X coordinate of the image 
//				INTN = Y coordinate of the image
//				BOOLEAN = Indicates whether to set the BGRT status field or not
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddImageDetailToACPI (UINT8 *ImageData, INTN CoordinateX, INTN CoordinateY, BOOLEAN GifImagePresence)
{
	EFI_STATUS  Status = EFI_SUCCESS;
	EFI_GUID    AcpiTableProtocolGuid = EFI_ACPI_TABLE_PROTOCOL_GUID;
    VOID        *AcpiTableBuffer = NULL;
    UINTN       AcpiTableBufferSize = 0;
	EFI_ACPI_TABLE_PROTOCOL *AcpiTableInstance = NULL;
    
	Status = gBS->LocateProtocol (&AcpiTableProtocolGuid, NULL, &AcpiTableInstance);
	if (EFI_SUCCESS != Status)
	{
		return;
	}
	FormBGRTTable (&AcpiTableBuffer, &AcpiTableBufferSize, ImageData, CoordinateX, CoordinateY, GifImagePresence);
    if (NULL != AcpiTableBuffer)
    {
        Status = AcpiTableInstance->InstallAcpiTable (AcpiTableInstance, AcpiTableBuffer, AcpiTableBufferSize, &gTableKey);
		if (EFI_SUCCESS == Status)
		{
			gBgrtSafeBuffer = AcpiTableBuffer;
		}
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CalculateChecksum
//
// Description:	Calculates the checksum for the given structure
//
// Input:		VOID => Table structure
//              UINT8 => Table Size
//
// Output:		UINT8 => Checksum for the table
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CalculateChecksum (VOID *AcpiTable, UINT8 TableSize)
{
    UINT8   *TablePtr = (UINT8 *)AcpiTable;
    UINT8   iIndex = 0;
    UINT8   Checksum = 0;

    for (iIndex= 0; iIndex < TableSize; iIndex ++)
    {
        Checksum += TablePtr [iIndex];        
    }    
    return (0 - Checksum);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BGRTSupportedLogoType
//
// Description:	Checks whether the BGRT data supports the specified logo
//
// Input:		UINT8 * => Data for the image
//
// Output:		BOOLEAN => TRUE if BGRT supports otherwise FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BGRTSupportedLogoType (UINT8 *ImageData)
{
    UINTN LogoType;
    LogoType = GetLogoType (ImageData);
    if (BMP_Logo== LogoType)
    {
        BMP_IMAGE_HEADER *BmpHeader;
        BmpHeader = (BMP_IMAGE_HEADER *)ImageData;
        if (24 == BmpHeader->BitPerPixel) 		//As per spec. BMP image should be 24 bitmap
        {    
            return TRUE;
        }
    }
    return FALSE;     
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------------------------------
// Procedure:	InvalidateStatusInBgrt
//
// Description:	Disables the BGRT status field if any changes happened in screen other than the image display
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InvalidateStatusInBgrt (VOID)
{
	EFI_STATUS  Status = EFI_SUCCESS;
	EFI_GUID    AcpiTableProtocolGuid = EFI_ACPI_TABLE_PROTOCOL_GUID;
	BGRT_TABLE  *BgrtTable;
	EFI_ACPI_TABLE_PROTOCOL *AcpiTableInstance = NULL;
	UINTN	TableSize = 0;
#if TSE_USE_EDK_LIBRARY
    UINT8 	AcpiHdrSize = sizeof (EFI_ACPI_DESCRIPTION_HEADER);
	EFI_ACPI_DESCRIPTION_HEADER *AcpiHdr;
#else
    UINT8 AcpiHdrSize = sizeof (ACPI_HDR);
	ACPI_HDR *AcpiHdr;
#endif
	TRACE((-1,"In InvalidateStatusInBgrt"));
	if (NULL == gBgrtSafeBuffer)		//EIP 58954 For BGRT table support
	{
		return;
	}
	BgrtTable = (BGRT_TABLE  *)((UINT8 *)gBgrtSafeBuffer + AcpiHdrSize);
	BgrtTable->Status = 0;
#if TSE_USE_EDK_LIBRARY
	AcpiHdr = (EFI_ACPI_DESCRIPTION_HEADER *)gBgrtSafeBuffer;
#else
	AcpiHdr = (ACPI_HDR *)gBgrtSafeBuffer;
#endif
	AcpiHdr->Checksum ++;			//Since changing the status bit from 1 to 0 adding checksum by 1.
	Status = gBS->LocateProtocol (&AcpiTableProtocolGuid, NULL, &AcpiTableInstance);
	if (EFI_SUCCESS != Status)
	{
		return;
	}
	Status = AcpiTableInstance->UninstallAcpiTable (AcpiTableInstance, gTableKey);
	if (EFI_SUCCESS != Status)
	{
		return;
	}
	gTableKey = 0;		//If not set to 0 then ACPI table is not created again
	TableSize = AcpiHdrSize + sizeof(BGRT_TABLE);
	Status = AcpiTableInstance->InstallAcpiTable (AcpiTableInstance, gBgrtSafeBuffer, TableSize, &gTableKey);
}

//EIP81830 starts - Support to uninstall the BGRT on legacy boot
//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------------------------------
// Procedure:	UninstallBGRT
//
// Description:	UninstallsBGRT table, Called for Legacy Boot
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UninstallBGRT (VOID)
{
	EFI_STATUS  Status = EFI_SUCCESS;
	EFI_GUID    AcpiTableProtocolGuid = EFI_ACPI_TABLE_PROTOCOL_GUID;
	BGRT_TABLE  *BgrtTable;
	EFI_ACPI_TABLE_PROTOCOL *AcpiTableInstance = NULL;
#if TSE_USE_EDK_LIBRARY
    UINT8 	AcpiHdrSize = sizeof (EFI_ACPI_DESCRIPTION_HEADER);
#else
    UINT8 AcpiHdrSize = sizeof (ACPI_HDR);
#endif
	TRACE((-1,"In UninstallBGRT"));

	if (NULL == gBgrtSafeBuffer)
	{
		return;
	}
	BgrtTable = (BGRT_TABLE  *)((UINT8 *)gBgrtSafeBuffer + AcpiHdrSize);

	Status = gBS->LocateProtocol (&AcpiTableProtocolGuid, NULL, &AcpiTableInstance);
	if (EFI_SUCCESS != Status)
	{
		return;
	}
	Status = AcpiTableInstance->UninstallAcpiTable (AcpiTableInstance, gTableKey);
	if (EFI_SUCCESS != Status)
	{
		return;
	}
    MemFreePointer((VOID**)&BgrtTable->ImageAddress);
    MemFreePointer((VOID**)&gBgrtSafeBuffer);

}
//EIP81830 ends

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 2012, American Megatrends, Inc.              **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*********************************************************************