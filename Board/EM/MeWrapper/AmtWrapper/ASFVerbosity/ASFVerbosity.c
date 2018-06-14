//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/ASF Verbosity/ASFVerbosity.c 2     4/24/12 12:46a Klzhan $
//
// $Revision: 2 $
//
// $Date: 4/24/12 12:46a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/ASF Verbosity/ASFVerbosity.c $
// 
// 2     4/24/12 12:46a Klzhan
// Update module to latest
// 
// 1     2/08/12 1:10a Klzhan
// Initial Check in 
// 
// 2     6/10/11 4:21a Klzhan
// Update ASF_INDUSTRY_IANA and ASF_INTEL_IANA ID.
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            ASFVerbosity.c
//
// Description:     Shows ASF POST Message
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <AmiDxeLib.h>
#include <Protocol\ConsoleControl.h>
#include <Protocol\SimpleTextOut.h>
#include <Protocol\SmBios.h>
#include <Protocol\SmbiosGetFlashDataProtocol.h>
#include <ReferenceCode\ME\Protocol\AlertStandardFormat\AlertStandardFormat.h>
#include <ReferenceCode\ME\Library\Amt\Include\Amt.h>

#define AMI_EFI_SOL_POST_MESSAGE_GUID \
{ 0xf42f3752, 0x12e, 0x4812, 0x99, 0xe6, 0x49, 0xf9, 0x43, 0x4, 0x84, 0x54 }

#define SOL_NORMAL 	0x00
#define SOL_VERB 	0x40
#define SOL_QUIET 	0x20
#define SOL_BLANK 	0x60
#define SOL_SETUP 	0x00

EFI_GUID guidEfiVar = EFI_GLOBAL_VARIABLE;
EFI_GUID gSmbiosProtocolGuid  = EFI_SMBIOS_PROTOCOL_GUID;
EFI_GUID gConsoleControlProtocolGuid = EFI_CONSOLE_CONTROL_PROTOCOL_GUID;
EFI_GUID gAmiEfiSolPostMessageGuid = AMI_EFI_SOL_POST_MESSAGE_GUID;


SMBIOS_TABLE_ENTRY_POINT    *SmBiosTableEntryPoint = 0;

static CHAR16  *SolString[] = {
    L"Intel Corporation. Copyright 2004-2009.\r\n",
    L"Intel Active Management Technology - Serial Over LAN operational mode.\r\n\r\n",
    L"BIOS Revision: ",
    L"\r\n\r\nBIOS Settings: <F2>\r\n",
#if defined SETUP_BBS_POPUP_ENABLE && SETUP_BBS_POPUP_ENABLE
    L"One Time Boot Menu: <F7>\r\n",
#else
    L"\r\n",
#endif
    L"Intel(R) AMT Client BIOS Setup Entry\r\n",
    L"Intel Remote PC Assist Technology - Serial Over LAN operational mode.\r\n\r\n",
};

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:                DMIHDR
//
// Description:	This structure represents DMI variable
//
// Fields:          Name           Type           Description
//          ------------------------------------------------------------------
//                  Type           UINT8          Type of DMI variable
//                  Length         UINT8          Length of the variable
//                  Handle         UINT16         SmBios handle for DMI
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT8     Type;
    UINT8     Length;
    UINT16    Handle;
} DMIHDR;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  AsciiStrLength
//
// Description: Computes Ascii string length including 0-terminator
//
// Input:
//    IN CHAR8 *String    Pointer to input ASCII string
//
//
//
// Output:
//    UINTN
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN AsciiStrLength(IN CHAR8* String)
{

    UINTN Length = 0;
    if (String == NULL)
        return Length;
    while (String[Length++] != 0);

    return Length;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  AsciiToUnicode
//
// Description: Transfer Ascii code to Unicode
//
// Input:
//    IN CHAR8 *String    Pointer to input ASCII string
//
//
//
// Output:
//    UINTN
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AsciiToUnicode (
    IN  CHAR8     *AsciiString,
    OUT CHAR16    *UnicodeString
)
{
    UINT8 Index = 0;

    while (AsciiString[Index] != 0) {
        UnicodeString[Index] = (CHAR16) AsciiString[Index];
        Index++;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  AsciiToUnicodeSmBiosString
//
// Description: Converts Ascii string to Unicode string
//
// Input:
//    IN CHAR8 *AsciiString             Pointer to input Ascii string
//    OUT CHAR16* UnicodeString         Pointer to output Unicode string
//
//
// Output:
//    VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AsciiToUnicodeSmBiosString
(
    IN CHAR8* AsciiString,
    OUT CHAR16* UnicodeString
)
{


    do {
        *(UnicodeString++) = (CHAR16)*AsciiString ;
    } while (*(AsciiString++) != 0);

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  GetSmBiosStructureLength
//
// Description: Finds the length of SmBios structure
//
// Input:
//    IN VOID* SmBiosStructure	Pointer to SmBios structure
//
// Output:
//    UINTN
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetSmBiosStructureLength
(
    IN VOID* SmBiosStructure
)
{

    UINT8* SmBiosStringsBlockPtr;
    UINTN Length = 0;
    SmBiosStringsBlockPtr = (UINT8*) SmBiosStructure + \
                            ((DMIHDR*)SmBiosStructure)->Length;
    while ( *(CHAR16*)(SmBiosStringsBlockPtr + Length) != 0) Length++;

    // determine the right value
    return ((DMIHDR*)SmBiosStructure)->Length + Length + 2;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  GetSmBiosStructureByHandle
//
// Description: Finds SmBios structure given a handle
//
// Input:
//    IN UINT16 Handle	Handle to SmBios structure
//
// Output:
//    VOID*	Pointer to SmBios structure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* GetSmBiosStructureByHandle
(
    IN UINT16 Handle
)
{

    UINT8* SmBiosStructurePtr = (UINT8*)(SmBiosTableEntryPoint->TableAddress);
    UINT8* SmBiosEnd = SmBiosStructurePtr + SmBiosTableEntryPoint->TableLength;

    while (SmBiosStructurePtr < SmBiosEnd) {

        if (((DMIHDR*)SmBiosStructurePtr)->Handle == Handle)
            return SmBiosStructurePtr;
        SmBiosStructurePtr += GetSmBiosStructureLength(SmBiosStructurePtr);
    }

    return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  GetSmBiosAsciiString
//
// Description: Finds SmBios data (Ascii string) inside SmBios structure
//
// Input:
//    IN VOID* SmBiosStructure	Pointer to SmBios structure
//	  IN UINT8 StringNumber		SmBios String number
//
// Output:
//    CHAR8*
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* GetSmBiosAsciiString
(
    IN VOID* SmBiosStructure, 
    IN UINT8 StringOffset
)
{

    CHAR8* SmBiosStringPtr;
    UINT8  StringNumber = *((UINT8*)SmBiosStructure + StringOffset);

    SmBiosStringPtr = (CHAR8*)SmBiosStructure + \
                        ((DMIHDR*)SmBiosStructure)->Length;
    if (StringNumber == 0)
        return NULL;

    if (SmBiosStructure != NULL)
        while ( (StringNumber--) != 1)
            SmBiosStringPtr += AsciiStrLength(SmBiosStringPtr);

    return SmBiosStringPtr;
}
EFI_ASF_BOOT_OPTIONS             *mAsfBootOptions = NULL;
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  DisplaySolMessageEvent
//
// Description: Dispaly Sol Message
//
// Input:
//
//
//
// Output:
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisplaySolMessageEvent(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS          Status;
    UINT8               i;
    UINT8               CastlePeak;
    UINTN               Size = 0;
    CHAR8               *SmBiosData = NULL;
    CHAR16              *SmBiosString;
    EFI_SMBIOS_PROTOCOL *SmbiosProtocol;
    EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode;
    EFI_CONSOLE_CONTROL_PROTOCOL *ConsoleControl;
    EFI_GUID gEfiAlertStandardFormatProtocolGuid = EFI_ALERT_STANDARD_FORMAT_PROTOCOL_GUID;
    EFI_ALERT_STANDARD_FORMAT_PROTOCOL  *Asf;
    Status = pBS->LocateProtocol (
                  &gEfiAlertStandardFormatProtocolGuid,
                  NULL,
                  &Asf
                  );
    if (EFI_ERROR (Status))
        return;

    Status = Asf->GetBootOptions (Asf, &mAsfBootOptions);
    if((mAsfBootOptions->IanaId != ASF_INTEL_CONVERTED_IANA) && 
       (mAsfBootOptions->IanaId != ASF_INDUSTRY_CONVERTED_IANA))
        return;
    Status = pBS->LocateProtocol (&gSmbiosProtocolGuid, NULL, &SmbiosProtocol);
    if (EFI_ERROR(Status))return;

    Status = pBS->LocateProtocol (&gEfiConsoleControlProtocolGuid, \
                                  NULL, (VOID**)&ConsoleControl);
    if (EFI_ERROR(Status))return;


    SmBiosTableEntryPoint = SmbiosProtocol->SmbiosGetTableEntryPoint();

    SmBiosData = GetSmBiosAsciiString( GetSmBiosStructureByHandle(0x00), 0x05);

    Size = AsciiStrLength(SmBiosData) + 1;

    Status = pBS->AllocatePool(EfiBootServicesData, \
             Size*sizeof(CHAR16), &SmBiosString);
    if (EFI_ERROR(Status))return;

    if (SmBiosData[0] != 0x20) {
        MemSet(SmBiosString, Size*sizeof(CHAR16), 0);
        AsciiToUnicodeSmBiosString(SmBiosData, SmBiosString);
    }

    CastlePeak = FALSE;
    ConsoleControl->GetMode(ConsoleControl, &ScreenMode, NULL, NULL);
    if (ScreenMode == EfiConsoleControlScreenGraphics) {
        ConsoleControl->SetMode( ConsoleControl, EfiConsoleControlScreenText );
    }
    pST->ConOut->EnableCursor( pST->ConOut, FALSE );
    pST->ConOut->ClearScreen( pST->ConOut);
    pST->ConOut->SetCursorPosition( pST->ConOut, 0, 0 );

    TRACE((-1,"mAsfBootOptions->BootOptions = %08x",mAsfBootOptions->BootOptions));

    // SOL Normal Mode and SOL Setup Mode
    switch (((mAsfBootOptions->BootOptions)>>8)) {
    case SOL_NORMAL:
    case SOL_VERB:

        for (i = 0; i <= 4; i++) {
            // AMT or Castle Peak ?
            if (i == 1 && CastlePeak) {
                pST->ConOut->OutputString ( pST->ConOut, SolString[6]);
            } else pST->ConOut->OutputString ( pST->ConOut, SolString[i]);

            if (i == 2)pST->ConOut->OutputString ( pST->ConOut, SmBiosString );
        }

        break;

    case SOL_QUIET:
        pST->ConOut->OutputString ( pST->ConOut, SolString[0]);
        pST->ConOut->OutputString ( pST->ConOut, L"\n\r");
        pST->ConOut->OutputString ( pST->ConOut, SolString[2]);
        pST->ConOut->OutputString ( pST->ConOut, SmBiosString);
        pST->ConOut->OutputString ( pST->ConOut, L"\n\r\n\r" );
        break;

    case SOL_BLANK:
        break;
    default:
        break;
    }//switch

    // SOL_SETUP
    if ((mAsfBootOptions->SpecialCommandParam & BIT3))
        pST->ConOut->OutputString ( pST->ConOut, SolString[5]);

    // Kill Event
    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  SolPostMessage
//
// Description: Sol Post Message
//
// Input:     NULL
//
//
// Output:    EFI_STATUS
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SolPostMessage(VOID)
{
    EFI_STATUS Status;
    VOID* Registration;
    EFI_EVENT gEvtSolMessage;


    //
    // Register for callback to 'AmiEfiSolPostMessage' protocol installation
    //
    Status = pBS->CreateEvent(
                 EFI_EVENT_NOTIFY_SIGNAL,
                 TPL_CALLBACK,
                 DisplaySolMessageEvent,
                 NULL,
                 &gEvtSolMessage
             );
    ASSERT_EFI_ERROR(Status);


    //
    // Register for protocol notifications on this event
    //
    Status = pBS->RegisterProtocolNotify (&gAmiEfiSolPostMessageGuid,
                                          gEvtSolMessage,
                                          &Registration);
    ASSERT_EFI_ERROR (Status);

    return EFI_SUCCESS;
}

EFI_STATUS ASFVerbosityEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    SolPostMessage();
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************