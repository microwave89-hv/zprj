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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetupext.c $
//
// $Author: Premkumara $
//
// $Revision: 16 $
//
// $Date: 8/28/14 8:37a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetupext.c $
// 
// 16    8/28/14 8:37a Premkumara
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
// 15    5/02/14 3:56a Premkumara
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
// 14    2/11/14 7:59p Arunsb
// [TAG]	EIP131739
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	UI is not Displaying properly after enabling Quite Boot
// [Root Cause]	While doing MainSetupLoopInit() it changes the mode to
// Text.
// [Solution]	A hook function is created in ESA which keeps the mode as
// Graphics
// [Files]	minisetupext.c
// 
// 13    12/04/13 2:10p Premkumara
// [TAG]	EIP123535
// [Category]	Improvement
// [Description]	Moved saving quietboot resolution to DrawQuietBootLogo()
// to avoid setting resolution of initPostScreenthis while booting.
// [Files]	commonoem.c, Boot.c, Logo.c, MinisetupExt.c
// 
// 12    12/04/13 5:29a Premkumara
// [TAG]	EIP123535
// [Category]	Improvement
// [Description]	Moved saving quietboot resolution to DrawQuietBootLogo()
// to avoid setting resolution of initPostScreenthis while booting.
// [Files]	commonoem.c, Boot.c, Logo.c, MinisetupExt.c
// 
// 11    3/16/13 4:02a Rajashakerg
// [TAG]  		EIP107221 
// [Category]  	Improvement
// [Description]  	Logo disappear after HDD password verified
// [Files]  		CommonHelper.c, notify.c, minisetupext.c
// 
// 10    10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 9     5/29/12 4:33a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 8     4/25/12 6:08a Rajashakerg
// [TAG]  		EIP86827 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	"gBootFlow" variable should be changed to
// BOOT_FLOW_CONDITION_NORMAL if we press ESC key from pop-pup menu
// [RootCause]  	ProcessProceedToBootHook() is not invoked when we press
// ESC key in the BBS popup Menu.
// [Solution]  	Fixed the issue by calling ProcessProceedToBootHook() when
// we press ESC key in the BBS popup Menu.
// [Files]  		BootOlny/minisetupext.c, TseLite/minisetupext.c.
// 
// 7     6/23/11 5:32a Rajashakerg
// [TAG]  		EIP63073  
// [Category]  	New Feature
// [Description]  	Source modules in TSE should get the version details
// from binary in run time not at build time  	
// [Files]  		CommonHelper.c, minisetupext.c, notify.c, Ezport\style.c,
// EzportPlus\style.c, Legacy\style.c
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 8     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/15/10 10:10p Madhans
// To avoid Compilation issues
// 
// 6     1/29/10 4:37p Madhans
// To not to depend on ConsoleControl and ConOut.
// 
// 5     1/09/10 5:28a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/13/09 7:35a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
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
// 3     5/13/09 2:22p Madhans
// To patch the version number in the Bootonly TSE. update the build
// number.
// 
// 2     5/07/09 10:35a Madhans
// Changes after Bin module
// 
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 3:59p Madhans
// fix in  ClearGrphxScreen
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
// Name:		MINISETUPEXT.C
//
// Description:	This file contains code for entrypoint and setup loop
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


//**************************** BBS POPUP CODE ********************************//

//#if SETUP_BBS_POPUP_ENABLE
extern EFI_GUID gBootNowCountGuid;
UINT16 gBBSPopupSel;

extern NVRAM_VARIABLE	*gOptimalDefaults;
extern UINTN CurrentScreenresolutionX, CurrentScreenresolutionY;//EIP-105717

struct DevName
{
	CHAR16 *String;
	int  Index;
} *gDevNames;

int gHiStr		= 0;
int gStrIdx		= 0;
int gNumOfDev	= 0;
CHAR16 *gBlankSpace = L"                                           ";
#define START_ROW_IDX	10
#define START_COL_IDX	20
#define MAX_STR_LEN		28
#define MAX_LENGTH		(MAX_STR_LEN+7)
#define MAX_DISP_LINES	8

#define _ENTER_KEY		0x0D
#define _ESC_KEY		0x170000
#define _UP_ARROW		0x10000
#define _DOWN_ARROW		0x20000

void CheckStrings(void);
void SetScrollPosition(int Index, int DirFlg);
INTN BBS_GetKey(VOID);
EFI_STATUS BbsPopupMenu( VOID );
void HighLightLine(int UpDown, int NumLines);
void DownDisplayList(int Start, int End, int NumLines);
void UpDisplayList(int Start, int End, int flag, int NumLines);
VOID MainSetupLoopInitHook(VOID);
UINT16 _BootSetBootNowCount(VOID);
CHAR16 *HiiGetStringLanguage( VOID* handle, UINT16 token, CHAR16 *lang );
UINT16 HiiChangeStringLanguage( VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string );
VOID GetTseBuildVersion(UINTN *TseMajor, UINTN *TseMinor, UINTN *TseBuild);//EIP 63073 : Source modules in TSE should get the version details from binary in run time not at build time
VOID GetTseBuildYear(UINT16 *TseBuildYear);//EIP 151966 : Use BIOS build year for copyright message
BOOLEAN 	IsMouseSupported(VOID);
BOOLEAN 	IsSoftKbdSupported(VOID);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearGrphxScreen
//
// Description:	Function to clear the graphics screen.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void ClearGrphxScreen(void)
{
	EFI_UGA_PIXEL UgaBlt={0,0,0,0};
	UINT32 HorizontalResolution = 0;
	UINT32 VerticalResolution = 0;
	EFI_STATUS Status = EFI_SUCCESS;

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	if(gGOP)
	{
		HorizontalResolution = gGOP->Mode->Info->HorizontalResolution;
		VerticalResolution = gGOP->Mode->Info->VerticalResolution;
	    Status = gGOP->Blt (
	    	gGOP,
	     	&UgaBlt,
	      	EfiBltVideoFill,
	       	0, 0,
	        0, 0,
	        HorizontalResolution, VerticalResolution,
	        0);
	}
#else
	if ( gUgaDraw != NULL )
	{
		gUgaDraw->GetMode (gUgaDraw, &HorizontalResolution, &VerticalResolution, &ColorDepth, &RefreshRate);
	    Status = gUgaDraw->Blt (
	    	gUgaDraw,
	     	&UgaBlt,
	      	EfiUgaVideoFill,           
	       	0, 0,
	        0, 0,
	        HorizontalResolution, VerticalResolution,
	        0);
	}
#endif
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoBbsPopupInit
//
// Description:	This function runs the loop for Pop up boot menu.
//              This function is responsible for creating the list
//              box control. It also gathers actions and passes them
//              to list box control and initiates draw sequence.
//
// Input:		BOOT_FLOW *BootFlow: Ptr to BOOT_FLOW responsible for
//              the call.
//
// Output:		Return Status based on errors that occurred in
//              library functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DoBbsPopupInit(VOID)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT16  i=0, u16BootCount = 2, *pu16BootCount = NULL;
	UINTN	size = 0;
	UINT16 count;

	PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);

	MainSetupLoopInitHook();

	count = (UINT16)gBootOptionCount;

	if(gPopupMenuShowAllBbsDev)
	    count = _BootSetBootNowCount();

	VarSetNvramName( L"BootNowCount", &gBootNowCountGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
	
	Status = VarLoadVariables( (VOID **)&gVariableList, (NVRAM_VARIABLE *)gOptimalDefaults );
	if ( EFI_ERROR( Status ) )
		return Status;

#if APTIO_4_00
		gMaxRows = MAX_ROWS;
		gMaxCols = MAX_COLS;
#endif

	pu16BootCount = VarGetNvramName( L"BootNowCount", &gBootNowCountGuid, NULL, &size );
	if(pu16BootCount)
		u16BootCount = *pu16BootCount;
	MemFreePointer(&pu16BootCount);

	//For Boot Only TSE
	gDevNames = EfiLibAllocatePool(u16BootCount * (sizeof(*gDevNames)));
	for (i=0; i<u16BootCount; i++) 
	{
		//EIP - 24971
		gDevNames[i].String = BootGetBootNowName(i,gPopupMenuShowAllBbsDev,BootNowInBootOrderSupport());
		//EIP - 24971
		gDevNames[i].Index = i;
	}

	gNumOfDev = u16BootCount;

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawBootOnlyBbsPopupMenu
//
// Description:	function for the BBS Popup menu
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawBootOnlyBbsPopupMenu( VOID )
{
	int		Row = 0;
	INTN	Key;
	int 	DispLines=0;
	int		EnoughOfThis = 0;

	if(gST->ConOut == NULL)
		return;

	SetDesiredTextMode();
	// Clean of the Graphics Screen
	ClearGrphxScreen();
	ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );

	//Initialise the global buffers
	InitializeScreenBuffer( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );

	//check the lengh of device strings, and truncate if it is out of boundaries
	CheckStrings();

	//Create heading
	DrawStringWithAttribute( START_COL_IDX+(MAX_STR_LEN/2)-4, START_ROW_IDX-2, L"BBS MENU", EFI_WHITE);
	DrawBorder( START_COL_IDX-3, START_ROW_IDX-3, MAX_LENGTH, 3);

	if( gNumOfDev < MAX_DISP_LINES )
	{
		DispLines = gNumOfDev;
	}
	else {
		DispLines = MAX_DISP_LINES;
	}
	//print all the avilable device info
	for( Row=START_ROW_IDX; Row < START_ROW_IDX+DispLines; Row++ ) {
		DrawStringWithAttribute( START_COL_IDX, Row, gDevNames[Row-START_ROW_IDX].String, EFI_LIGHTGRAY);
	}
	DrawBorder( START_COL_IDX-3, START_ROW_IDX-1, MAX_LENGTH, DispLines+2);

	//keep the cursor in the staring line of strings display
	gST->ConOut->SetCursorPosition( gST->ConOut, START_COL_IDX, START_ROW_IDX );

	//highlight first option in the list by default
	DrawStringWithAttribute( START_COL_IDX, START_ROW_IDX, gDevNames[0].String, EFI_WHITE);
	DrawBorder( START_COL_IDX-3, START_ROW_IDX-1, MAX_LENGTH, DispLines+2);

	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX+MAX_LENGTH-4),BOXDRAW_VERTICAL_LEFT, EFI_WHITE );
	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX-3),BOXDRAW_VERTICAL_RIGHT, EFI_WHITE );

	SetScrollPosition(DispLines, 2);
	FlushLines( 0, gMaxRows - 1 );
	DoRealFlushLines();

	while(TRUE)
	{
		//Get input key
		Key = BBS_GetKey();

		if(_ESC_KEY == Key) {
			PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);
			gBBSPopupSel = 0 ;
			EnoughOfThis = 1 ;
			ProcessProceedToBootHook();//EIP 86827 : When ESC pressed in the BBS popup menu 
			break;
		}

		switch(Key)
		{
			case _DOWN_ARROW:
				if(gStrIdx<(gNumOfDev-1)) {
					gStrIdx++;
					if( gHiStr >= (DispLines-1) ) {
						DownDisplayList(gStrIdx-(DispLines-1), gStrIdx, DispLines);
					}
					else {
						HighLightLine(0, DispLines);
					}
				}
			break;

			case _UP_ARROW:

				if(gStrIdx > 0) {
					gStrIdx--;
					if( gHiStr == 0 ) {
						if(gStrIdx>=0)
							UpDisplayList(gStrIdx, gStrIdx+(DispLines-1), 0, DispLines);
					}
					else if( gHiStr > 0 ) {
						HighLightLine(1, DispLines);
					}
				}
			break;

			case _ENTER_KEY:
				if( ( gStrIdx >= 0) && ( gStrIdx <= gNumOfDev) ) {
					//call the function with the selected device index
					PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);
					gBBSPopupSel = (UINT16) gStrIdx ;
					EnoughOfThis = 1 ;
				}
				break;
		}
		DoRealFlushLines();
		if(EnoughOfThis)
			break ;
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BbsBoot
//
// Description:	This function is a hook called after launching
//              BBS Popup Menu. This function is available as
//              ELINK. In the generic implementation this function is
//              empty. OEMs may choose to do additional logic here.
//
// Input:		index: The nth option in the boot now menu.
//				ShowAllBbsDev - SETUP_SHOW_ALL_BBS_DEVICES
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BbsBoot(VOID)
{
	if(gEnterSetup != TRUE)
		BootLaunchBootNow(gBBSPopupSel, gPopupMenuShowAllBbsDev) ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BbsStrnCpy
//
// Description:	function the string copy
//
// Input:		CHAR16  *Dst, CHAR16  *Src, UINTN   Length
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BbsStrnCpy ( CHAR16  *Dst, CHAR16  *Src, UINTN   Length )
{
	UINTN Index;
	UINTN SrcLen;

	SrcLen = EfiStrLen (Src);

	Index = 0;
	while (Index < Length && Index < SrcLen) {
		Dst[Index] = Src[Index];
		Index++;
	}

	for (Index = SrcLen; Index < Length; Index++) {
		Dst[Index] = 0;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBS_GetKey
//
// Description:	function to read the input key
//
// Input:		void
//
// Output:		ScanCode/UniCode
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN BBS_GetKey(VOID)
{
    EFI_INPUT_KEY	    Key;
    UINTN Index;

    // flush keyboard buffer
    while ( gST->ConIn->ReadKeyStroke(gST->ConIn,&Key) == EFI_SUCCESS );

    gBS->WaitForEvent( 1, &gST->ConIn->WaitForKey, &Index );
    gST->ConIn->ReadKeyStroke(gST->ConIn,&Key);
    return (Key.ScanCode<<16)|Key.UnicodeChar;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckStrings
//
// Description:	function to validate the stings
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void CheckStrings(void)
{
	int idx;
	UINTN Length=0;
	CHAR16  TmpStr[50];

	for( idx=0; idx < gNumOfDev; idx++ ) {


		Length = EfiStrLen( gDevNames[idx].String );

		if(Length > MAX_STR_LEN)
		{
			BbsStrnCpy(TmpStr,L" ",MAX_STR_LEN);
			BbsStrnCpy(TmpStr, gDevNames[idx].String, (MAX_STR_LEN-3));
			EfiStrCpy (TmpStr + EfiStrLen(TmpStr),L"...");

			BbsStrnCpy(gDevNames[idx].String,L" ",Length);
			BbsStrnCpy(gDevNames[idx].String, TmpStr, MAX_STR_LEN);
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetScrollPosition
//
// Description:	function to set the position of the Scroll bar
//
// Input:		int Index, int DirFlg
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetScrollPosition(int Index, int DirFlg)
{
	if(gNumOfDev > MAX_DISP_LINES)
	{
		if(DirFlg==2) {
			WriteCharWithAttribute( (START_ROW_IDX+Index-1), (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_DOWN_TRIANGLE, EFI_WHITE );
		}
		else if( (DirFlg==0) && (gStrIdx>Index-1) ) {
			if(gStrIdx!= gNumOfDev-1)
				WriteCharWithAttribute( (START_ROW_IDX+Index-1), (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_DOWN_TRIANGLE, EFI_WHITE );
			WriteCharWithAttribute( START_ROW_IDX, (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_UP_TRIANGLE, EFI_WHITE );
		}
		else if( (DirFlg==1) && (gStrIdx<gNumOfDev-Index) ) {
			WriteCharWithAttribute( (START_ROW_IDX+Index-1), (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_DOWN_TRIANGLE, EFI_WHITE );
			if(gStrIdx!= 0)
				WriteCharWithAttribute( START_ROW_IDX, (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_UP_TRIANGLE, EFI_WHITE );
		}
		else if(DirFlg==0) {
			WriteCharWithAttribute( (START_ROW_IDX+Index-1), (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_DOWN_TRIANGLE, EFI_WHITE );
		}
		else if(DirFlg==1) {
			WriteCharWithAttribute( START_ROW_IDX, (START_COL_IDX+MAX_LENGTH-5),GEOMETRICSHAPE_UP_TRIANGLE, EFI_WHITE );
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpDisplayList
//
// Description:	function to display the upside list
//
// Input:		int Start, int End, int flag, int NumLines
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void UpDisplayList(int Start, int End, int flag, int NumLines)
{
	int RowNum, i;

	i= End;
	for( RowNum=START_ROW_IDX; Start<=End; RowNum++ ) {
		DrawStringWithAttribute( START_COL_IDX, RowNum, gBlankSpace, 0);
		DrawStringWithAttribute( START_COL_IDX, RowNum, gDevNames[Start++].String, EFI_LIGHTGRAY);
	}
	DrawStringWithAttribute( START_COL_IDX, (RowNum-NumLines), gBlankSpace, 0);
	DrawStringWithAttribute( START_COL_IDX, (RowNum-NumLines), gDevNames[Start-NumLines].String, EFI_WHITE);
	DrawBorder( START_COL_IDX-3, START_ROW_IDX-1, MAX_LENGTH, (NumLines+2));

	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX+MAX_LENGTH-4),BOXDRAW_VERTICAL_LEFT, EFI_WHITE );
	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX-3),BOXDRAW_VERTICAL_RIGHT, EFI_WHITE );

	SetScrollPosition(NumLines, 1);

	FlushLines( 0, gMaxRows - 1 );

	if(gHiStr) gHiStr--;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DownDisplayList
//
// Description:	function to display the downside list
//
// Input:		int Start, int End, int NumLines
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DownDisplayList(int Start, int End, int NumLines)
{
	int RowNum;

	for( RowNum=START_ROW_IDX; Start<End; RowNum++ ) {
		DrawStringWithAttribute( START_COL_IDX, RowNum, gBlankSpace, 0);
		DrawStringWithAttribute( START_COL_IDX, RowNum, gDevNames[Start++].String, EFI_LIGHTGRAY);
	}
	DrawStringWithAttribute( START_COL_IDX, RowNum, gBlankSpace, 0);
	DrawStringWithAttribute( START_COL_IDX, RowNum, gDevNames[End].String, EFI_WHITE);
	DrawBorder( START_COL_IDX-3, START_ROW_IDX-1, MAX_LENGTH, (NumLines+2));

	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX+MAX_LENGTH-4),BOXDRAW_VERTICAL_LEFT, EFI_WHITE );
	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX-3),BOXDRAW_VERTICAL_RIGHT, EFI_WHITE );

	SetScrollPosition(NumLines, 0);
	FlushLines( 0, gMaxRows - 1 );

	if(gHiStr<(NumLines-1)) gHiStr++;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HighLightLine
//
// Description:	function to hilight a perticular line
//
// Input:		int UpDown, int NumLines
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void HighLightLine(int UpDown, int NumLines)
{

	if(UpDown) {
		DrawStringWithAttribute( START_COL_IDX, (START_ROW_IDX+gHiStr-1), gDevNames[gStrIdx].String, EFI_WHITE);
		DrawStringWithAttribute( START_COL_IDX, (START_ROW_IDX+gHiStr), gDevNames[gStrIdx+1].String, EFI_LIGHTGRAY);
		DrawBorder( START_COL_IDX-3, START_ROW_IDX-1, MAX_LENGTH, (NumLines+2));
	}
	else {
		DrawStringWithAttribute( START_COL_IDX, (START_ROW_IDX+gHiStr+1), gDevNames[gStrIdx].String, EFI_WHITE);
		DrawStringWithAttribute( START_COL_IDX, (START_ROW_IDX+gHiStr), gDevNames[gStrIdx-1].String, EFI_LIGHTGRAY);
		DrawBorder( START_COL_IDX-3, START_ROW_IDX-1, MAX_LENGTH, (NumLines+2));
	}
	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX+MAX_LENGTH-4),BOXDRAW_VERTICAL_LEFT, EFI_WHITE );
	WriteCharWithAttribute( START_ROW_IDX-1, (START_COL_IDX-3),BOXDRAW_VERTICAL_RIGHT, EFI_WHITE );

	SetScrollPosition(NumLines, UpDown);
	FlushLines( 0, gMaxRows - 1 );

	if(UpDown) {
		if( gHiStr>0 ) gHiStr--;
	}
	else{
		if( gHiStr<(NumLines-1) ) gHiStr++;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitgProgress
//
// Description:	
//
// Input:		No Arguments
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitgProgress( VOID )
{
	gProgress = EfiLibAllocateZeroPool(sizeof (PROGRESSBAR_INFO) );
	gProgress->quiteBootActive = FALSE ;
	gProgress->active = FALSE ;
	gProgress->completed = 0 ;
	gProgress->delta = 0 ;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootOnlyUpdateVersionString	
//
// Description:	Function to update version string
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BootOnlyUpdateVersionString( VOID )
{
	CHAR16 *string = NULL, *newString = NULL;
	UINTN length,TseMajor,TseMinor, TseBuild;
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
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SavePostScreen	
//
// Description:	Function to save the post screen
//
// Input:		UINTN *SizeOfX, UINTN *SizeOfY 
//
// Output:		VOID*
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *SavePostScreen( UINTN *SizeOfX, UINTN *SizeOfY )
{
	EFI_UGA_PIXEL *UgaBlt = NULL;
	UINTN UgaBltSize;
	EFI_STATUS Status = EFI_UNSUPPORTED;

	UpdateGoPUgaDraw();//EIP:50479 : Function to Update gGop before using it in AMITSE.

	MouseStop();
	if ( gQuietBoot )
	{
	     if(EFI_SUCCESS == GetScreenResolution(SizeOfX,SizeOfY))
	     {
	         UgaBltSize = (*SizeOfX) * (*SizeOfY) * sizeof(EFI_UGA_PIXEL);
	         UgaBlt = EfiLibAllocatePool(UgaBltSize);
	
	         if(UgaBlt)
	         {
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	             Status = gGOP->Blt(
	                     gGOP,
	                     UgaBlt,
	                     EfiBltVideoToBltBuffer,
	                     0, 0,
	                     0, 0,
	                     *SizeOfX, *SizeOfY,
	                     0);
#else
	             Status = gUgaDraw->Blt(
	                     gUgaDraw,
	                     UgaBlt,
	                     EfiBltVideoToBltBuffer,           
	                     0, 0,
	                     0, 0,
	                     *SizeOfX, *SizeOfY,
	                     0);
#endif
	         }
	     }
	}	

	MouseRefresh();
	return (VOID *)UgaBlt;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RestorePostScreen	
//
// Description:	Function to restore the saved screen
//
// Input:		VOID *UgaBlt, UINTN SizeOfX, UINTN SizeOfY 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestorePostScreen( VOID *UgaBlt, UINTN SizeOfX, UINTN SizeOfY )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_UGA_PIXEL *Buffer = (EFI_UGA_PIXEL *)UgaBlt;

	MouseStop();	
	if ( Buffer )
    {
		if(gConsoleControl != NULL)
            gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenGraphics );
			
		if( (NULL != gGOP) && (SizeOfX && SizeOfY) && //If it has vaild gGOP and Resolution
			( (SizeOfX != gGOP->Mode->Info->HorizontalResolution) || (SizeOfY != gGOP->Mode->Info->VerticalResolution) ) //If QuietBoot resolution is differ
		)//EIP-105717
		{
			GOPSetScreenResolution(&SizeOfX, &SizeOfY);
		}

	if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
		MouseInit();

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
        Status = gGOP->Blt (
                gGOP,
                Buffer,
                EfiBltBufferToVideo,
                0, 0,
                0, 0,
                SizeOfX, SizeOfY,
                0);
#else
        Status = gUgaDraw->Blt (
                gUgaDraw,
                Buffer,
                EfiUgaBltBufferToVideo,           
                0, 0,
                0, 0,
                SizeOfX, SizeOfY,
                0);
#endif
    }

	MouseRefresh();
	// If ConOut is available in System Table the activate the post screen.
	if ( gST->ConOut != NULL ) 
    {
    	//Show post screen if it is not quiet boot or if it is a headless system
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
        if ( ! gQuietBoot || !gGOP)
#else
    	if ( ! gQuietBoot || !gUgaDraw)
#endif
    	{
    		//Clear the flush buffer to avoid messages missing
    		MemSet(gFlushBuffer, sizeof(SCREEN_BUFFER), 0);
    
    		CleanUpLogo();
    		InitPostScreen();
    	}
    }    
	MemFreePointer((VOID **) &Buffer);

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
