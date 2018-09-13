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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/print.c $
//
// $Author: Arunsb $
//
// $Revision: 9 $
//
// $Date: 5/21/14 6:27p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/print.c $
// 
// 9     5/21/14 6:27p Arunsb
// [TAG]	EIPEIP169096,168632
// [Description]	Changed global variable guid usage for tse debug messages
// [Files]	commonoem.c, setupdbg.h and print.c
// 
// 8     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     5/29/12 4:34a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 6     11/14/11 2:58p Blaines
// [TAG] - EIP 75481
// [Category]- Function Request
// [Synopsis]- TSE debug print infrastructure.
// [Description]- Add TSE debug print info for basic functions such as
// Hiiparsing, HiiNotifications, HiiCallbacks. Variables, and Ifrforms
// data. 
// [Files]
// AMITSE.sdl, AmiTSEStr.uni,  CommonHelper.c, commonoem.c, FakeTokens.c
// Globals.c, Minisetup.cif, Minisetup.h, print.c, FormBrowser2.c, Hii.c,
// HiiCallback.c, HiiNotificationHandler.c, Parse.c, TseUefiHii.h,
// Uefi21Wrapper.c, setupdbg.h
// 
// Update an incorrect string field.
// 
// 5     11/14/11 2:43p Blaines
// [TAG] - EIP 75481
// [Category]- Function Request
// [Synopsis]- TSE debug print infrastructure.
// [Description]- Add TSE debug print info for basic functions such as
// Hiiparsing, HiiNotifications, HiiCallbacks. Variables, and Ifrforms
// data. 
// [Files]
// AMITSE.sdl, AmiTSEStr.uni,  CommonHelper.c, commonoem.c, FakeTokens.c
// Globals.c, Minisetup.cif, Minisetup.h, print.c, FormBrowser2.c, Hii.c,
// HiiCallback.c, HiiNotificationHandler.c, Parse.c, TseUefiHii.h,
// Uefi21Wrapper.c, setupdbg.h
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 5     2/15/10 10:11p Madhans
// to avoid compilation issues
// 
// 4     6/24/09 6:09p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
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
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
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
// Name:		Print.c
//
// Description:	file contains code to support the print functionalities
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

/*++
  VSPrint, Print, SPrint format specification has the follwoing form

  %[flags][width]type

  flags:
    '-' - Left justify
    '+' - Prefix a sign
    ' ' - Prefix a blank
    ',' - Place commas in numberss
    '0' - Prefix for width with zeros
    'l' - UINT64
    'L' - UINT64

  width:
    '*' - Get width from a UINTN argumnet from the argument list
    Decimal number that represents width of print

  type:
    'X' - argument is a UINTN hex number, prefix '0'
    'x' - argument is a hex number
    'd' - argument is a decimal number
    'a' - argument is an ascii string 
    'S','s' - argument is an Unicode string
    'g' - argument is a pointer to an EFI_GUID
    't' - argument is a pointer to an EFI_TIME structure
    'c' - argument is an ascii character
    'r' - argument is EFI_STATUS
    '%' - Print a %

--*/
#include "minisetup.h"
#include "setupdbg.h"

#if !TSE_USE_EDK_LIBRARY

typedef struct _EFI_PRINT_PROTOCOL EFI_PRINT_PROTOCOL;

typedef UINTN (EFIAPI *EFI_VSPRINT)(
	OUT CHAR16 *StartOfBuffer, IN UINTN BufferSize,
	IN CONST CHAR16 *FormatString, IN va_list Marker
);
extern EFI_GUID gEfiPrintProtocolGuid;
struct _EFI_PRINT_PROTOCOL{
	EFI_VSPRINT VSPrint;
};

#else

#include "Tiano.h"
#include "EfiDriverLib.h"
#include "TianoCommon.h"
#include "EfiCommonLib.h"
#include "EfiPrintLib.h"

#endif

//EIP75481  Support TSE debug print infrastructure
#if TSE_DEBUG_MESSAGES

extern BOOLEAN SetupDebugKeyHandler(UINT16 ItemIndex, UINT16 Unicode, CHAR16	*Value) ;
extern EFI_STATUS DisplayParseFormSetData(VOID) ;
extern EFI_STATUS DebugShowAllHiiVariable(UINT32 formID);
#endif
//typedef CHAR16  CHAR_W;
#if TSE_APTIO_5_SUPPORT
#define AMITSE_VSPrint  Swprintf_s_va_list
#else
#define AMITSE_VSPrint  VSPrint
#endif
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	VSPrint
//
// Description:	VSPrint function to process format and place the results in Buffer. Since a 
//				VA_LIST is used this rountine allows the nesting of Vararg routines. Thus 
//				this is the main print working routine
//
// Input:		StartOfBuffer - Unicode buffer to print the results of the parsing of Format into.
//				BufferSize    - Maximum number of characters to put into buffer. Zero means no limit.
//				FormatString  - Unicode format string see file header for more details.
//				Marker        - Vararg list consumed by processing Format.
//
// Output:		Number of characters printed.
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
VSPrint (
  OUT CHAR16        *StartOfBuffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR16  *FormatString,
  IN  VA_LIST       Marker
  )
{
  EFI_STATUS          Status;
  EFI_PRINT_PROTOCOL  *PrintProtocol;

  Status = gBS->LocateProtocol (
                  &gEfiPrintProtocolGuid,
                  NULL,
                  &PrintProtocol
                  );
  if (EFI_ERROR (Status)) {
    return 0;
  } else {
    return PrintProtocol->VSPrint (
                            StartOfBuffer,
                            BufferSize,
                            FormatString,
                            Marker
                            );
  }
}



//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	SPrint
//
// Description:	SPrint function to process format and place the results in Buffer
//
// Input:		Buffer     - Wide char buffer to print the results of the parsing of Format into.
//					BufferSize - Maximum number of characters to put into buffer. Zero means no limit.
//					Format - Format string see file header for more details.
//					...    - Vararg list consumed by processing Format.
//
// Output:		Number of characters printed.
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
SPrint (
  OUT CHAR16        *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR16  *Format,
  ...
  )
{
  UINTN   Return;
  VA_LIST Marker;

  VA_START (Marker, Format);
  Return = AMITSE_VSPrint(Buffer, BufferSize, Format, Marker);
  VA_END (Marker);

  return Return;
}

#define MAX_DEBUG_STRING_SIZE 1000

CHAR16  tmpBuffer[MAX_DEBUG_STRING_SIZE];

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	SetupDebugPrint
//
// Description:	
//
// Input:		
//
// Output:		
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetupDebugPrint(IN CONST CHAR8  *Format, ...)
{
    UINTN   Return = 0;
    VA_LIST Marker;
    CHAR16 *c16Format = (CHAR16 *)NULL;
    CHAR8 *trace = NULL;

    c16Format = StrDup8to16((CHAR8  *)Format);

    VA_START (Marker, Format);
    Return = AMITSE_VSPrint(tmpBuffer, MAX_DEBUG_STRING_SIZE, (CONST CHAR16 *)c16Format, Marker);
    VA_END (Marker);

    //For TRACE (Serial Output)
#if SERIAL_DEBUG
//    TRACE(-1, Format, Marker);

  trace = StrDup16to8(tmpBuffer);
  TRACE ((-1, trace));
  MemFreePointer( (VOID **)&trace );

#else //Else of SERIAL_DEBUG

#if SCREEN_PRINT
    Print(tmpBuffer);
#else //Else of SCREEN_PRINT
    if(gST->ConOut){
        gST->ConOut->OutputString( gST->ConOut, tmpBuffer );
    }
#endif //End of SCREEN_PRINT
#endif //End of SERIAL_DEBUG
    MemFreePointer( (VOID **)&c16Format );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    SetupShowDebugScreen
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//extern VOID HandleDebugDumpKey( VOID *app, VOID *hotkey, VOID *cookie );
VOID SetupShowDebugScreen(VOID *app, VOID *hotkey, VOID *cookie )
{

#if TSE_DEBUG_MESSAGES    
    CHAR16  HiiParseing[2]          = L"x" ;
    CHAR16  HiiFunction[2]          = L"x" ;
    CHAR16  HiiNotification[2]      = L"x"; 
    CHAR16  HiiCallback[2]          = L"x" ;
    CHAR16  PrintIfrForm[27]        = L"press any key" ;
    CHAR16  PrintVariableCache[27]  = L"press any key" ; 

    TEXT_INPUT_TEMPLATE SetupDebugItems[6] = 
    {
        {STRING_TOKEN(STR_DBG_PRINT_HIIPARSING), 1, TSE_FILTER_KEY_CUSTOM, FALSE, HiiParseing},
        {STRING_TOKEN(STR_DBG_PRINT_HIIFUNCTION), 1, TSE_FILTER_KEY_CUSTOM, FALSE, HiiFunction},
        {STRING_TOKEN(STR_DBG_PRINT_HIICALLBACK), 1, TSE_FILTER_KEY_CUSTOM, FALSE, HiiCallback},
        {STRING_TOKEN(STR_DBG_PRINT_HIINOTIFICATION) , 1, TSE_FILTER_KEY_CUSTOM, FALSE, HiiNotification},
        {STRING_TOKEN(STR_DBG_PRINT_IFRFORM), 13, TSE_FILTER_KEY_CUSTOM, FALSE, PrintIfrForm},
        {STRING_TOKEN(STR_DBG_PRINT_VARIABLE_CACHE), 13, TSE_FILTER_KEY_CUSTOM, FALSE, PrintVariableCache}
    };
    
    UINT16 Title = HiiAddString( gHiiHandle, L"TSE Debug Print") ;

    if((gDbgPrint & PRINT_UEFI_PARSE)!= PRINT_UEFI_PARSE)
        EfiStrCpy( HiiParseing, L" ") ;

    if((gDbgPrint & PRINT_UEFI)!= PRINT_UEFI)
        EfiStrCpy( HiiFunction, L" ") ;

    if((gDbgPrint & PRINT_UEFI_NOTIFICATION)!= PRINT_UEFI_NOTIFICATION)
        EfiStrCpy( HiiNotification, L" ") ;

    if((gDbgPrint & PRINT_UEFI_CALLBACK)!= PRINT_UEFI_CALLBACK)
        EfiStrCpy( HiiCallback, L" ") ;      

    

    PostManagerDisplayTextBox(
			gHiiHandle,
            Title,
            SetupDebugItems, 
            6,
            SetupDebugKeyHandler
			) ;
#endif    
}

#if TSE_DEBUG_MESSAGES

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    SetupShowDebugScreen
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetupToggleDebugFeature(UINT16 FeatureBit, CHAR16 *Value)
{
    
    EFI_STATUS Status = EFI_UNSUPPORTED;
    EFI_GUID    guidDbgPrint = TSE_DEBUG_MESSAGES_GUID;  
    
    if((gDbgPrint & FeatureBit)== FeatureBit)
    {
        gDbgPrint &= ~((UINT16)FeatureBit) ;    
        EfiStrCpy( Value, L" ") ;
    }
    else
    {
        gDbgPrint |= (UINT16)FeatureBit ;
        EfiStrCpy( Value, L"x");
    }

    Status = pRS->SetVariable(L"TseDebugPrint", 
        &guidDbgPrint,
        EFI_VARIABLE_NON_VOLATILE |
        EFI_VARIABLE_BOOTSERVICE_ACCESS,
        sizeof(gDbgPrint),
        &gDbgPrint);  

  
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    SetupDebugKeyHandler
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SetupDebugKeyHandler(UINT16 ItemIndex, UINT16 Unicode, CHAR16 *Value)
{
          
    switch(ItemIndex)
	{
	    case 0:
            SetupToggleDebugFeature(PRINT_UEFI_PARSE, Value) ;
            break ;
        case 1:
            SetupToggleDebugFeature(PRINT_UEFI, Value) ;
            break ;
        case 2:
            SetupToggleDebugFeature(PRINT_UEFI_CALLBACK, Value) ;
            break ;
        case 3:    
            SetupToggleDebugFeature(PRINT_UEFI_NOTIFICATION, Value) ;
            break ;
        case 4:
		    DisplayParseFormSetData() ;
		    break;
	    case 5:
            DebugShowAllHiiVariable(0) ;
            break;
	    default:
            
		    break;
	}
           
	return TRUE ;
}


#endif //End of TSE_DEBUG_MESSAGES
//EIP75481

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
