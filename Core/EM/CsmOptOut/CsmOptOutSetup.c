//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

///**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOutSetup.c 10    7/08/13 4:17p Artems $
//
// $Revision: 10 $
//
// $Date: 7/08/13 4:17p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOutSetup.c $
// 
// 10    7/08/13 4:17p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Build error
// [RootCause]  	Unreferenced local variable
// [Solution]  	Removed variable
// [Files]  		CsmOptOutSetup.c
// 
// 9     7/02/13 5:06p Artems
// [TAG]  		EIP125900
// [Category]  	Improvement
// [Description]  	Funciton IsUefiGop assumed, that GOP protocol installed
// on the same handle
// where PciIO is installed, which is not always the case.
// Updated to handle different cases
// [Files]  		CsmOptOutSetup.c
// 
// 8     2/26/13 1:47p Artems
// [TAG]  		EIP111710
// [Category]  	Improvement
// [Description]  	Added multilanguage support for error message box
// [Files]  		CsmOptOutSetup.c
// 
// 7     1/22/13 4:29p Artems
// [TAG]  		EIP111710
// [Category]  	Improvement
// [Description]  	Replace MessageBox message and title with string tokens
// to allow
// different language usage
// [Files]  		CsmOptOut.mak CsmOptOut.uni CsmOptOutSetup.c
// 
// 6     9/27/12 7:14p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Secureboot enable callbacks moved to Secure Boot module
// [Files]  		CsmOptOut.sdl CsmOptOutSetup.c
// 
// 5     9/11/12 5:26p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Changed dependency on secureboot pkg module revision
// [Files]  		CsmOptOutSetup.c
// 
// 4     9/04/12 3:15p Artems
// [TAG]  		EIP98995
// [Category]  	Improvement
// [Description]  	Use EFI_UNSUPPORTED status in Browser callback to
// discard control value instead of FORM_DISCARD
// [Files]  		CsmOptOutSetup.c
// 
// 3     8/29/12 2:26p Artems
// [TAG]  		EIP98995
// [Category]  	Improvement
// [Description]  	When enable secure boot disable CSM but preserve CSM
// optout options setting,
// so once secure boot is disabled they can be restored
// [Files]  		CsmOptOut.sd, CsmOptOut.sdl, CsmOptOutSetup.c
// CsmOptOutRuntime.c
// 
// 2     6/20/12 6:10p Artems
// [TAG]  		EIP83692
// [Category]  	Improvement
// [Description]  	CSM OptOut setup page grayed out if secure boot is
// enabled
// CSM OptOut PlatformOverride protocol modified to fix SCT bugs
// Removed support for Launch CSM "Auto" option
// 
// [Files]  		CsmOptOut.c CsmOptOut.mak CsmOptOut.sd CsmOptOut.sdl
// CsmOptOut.uni CsmOptOutRuntime.c CsmOptOutSetup.c
// 
// 1     5/21/12 4:34p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Prevent user from disable CSM in setup if active video
// is legacy
// [Files]  		CsmOptOutSetup.c CsmOptOut.sdl CsmOptOut.mak 
// CsmOptOut.sdl
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CsmOptOutSetup.c
//
// Description: Implementation of interactive callback to "Launch CSM" setup control
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include <AmiLoadCsmPolicy.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DevicePath.h>
#include <Protocol/PciIo.h>
#include <Protocol/AmiPostMgr.h>
#include <Protocol/HiiString.h>

static EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
static EFI_GUID AmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
static AMI_POST_MANAGER_PROTOCOL* AmiPostMgr = NULL;

extern const char *DefaultLanguageCode;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    IsUefiGop
// 
// Description:  This function checks wheter passed controller is managed by  UEFI GOP driver
//               
//  Input:
// 	IN EFI_HANDLE pci_hnd - handle of the controller
//
//  Output:
//  0 - controller managed by legacy driver
//  1 - controller managed by UEFI driver
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsUefiGop(
    IN EFI_HANDLE pci_hnd
)
{
    EFI_STATUS Status;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *ent;
    UINTN n_ent;
    UINTN i;
    VOID *p;
    static EFI_GUID AmiCsmThunkProtocolGuid = AMI_CSM_THUNK_PROTOCOL_GUID;
    BOOLEAN Result = TRUE;

    Status = pBS->OpenProtocolInformation(pci_hnd, &gEfiPciIoProtocolGuid, &ent, &n_ent);
    if(EFI_ERROR(Status))
        return FALSE;

    for(i = 0; i < n_ent; i++) {
        if(!(ent[i].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER))
            continue;

        Status = pBS->HandleProtocol(ent[i].AgentHandle, &AmiCsmThunkProtocolGuid, &p);
        if(!EFI_ERROR(Status)) {
            Result = FALSE;
            break;
        }
    }
    pBS->FreePool(ent);

    return Result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    IsLegacyVideo
// 
// Description:  This function checks if active video is Legacy or UEFI
//               
//  Input:
// 	None
//
//  Output:
//  0 - active video is UEFI
//  1 - active vide is Legacy
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsLegacyVideo(
    VOID
)
{
    EFI_STATUS Status;
    EFI_HANDLE *hnd;
    EFI_HANDLE pci_hnd;
    UINTN n_hnd;
    UINTN i;
    EFI_DEVICE_PATH_PROTOCOL *dp;

    Status = pBS->LocateHandleBuffer(ByProtocol, &gEfiGraphicsOutputProtocolGuid, NULL, &n_hnd, &hnd);
    if(EFI_ERROR(Status))
        return FALSE;

    for(i = 0; i < n_hnd; i++) {
        Status = pBS->HandleProtocol(hnd[i], &gEfiDevicePathProtocolGuid, &dp);
        if(EFI_ERROR(Status))
            continue;
        Status = pBS->LocateDevicePath(&gEfiPciIoProtocolGuid, &dp, &pci_hnd);
        if(EFI_ERROR(Status))
            continue;

        if(IsUefiGop(pci_hnd))
            return FALSE;
    }
    pBS->FreePool(hnd);
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetCurrentLanguage
//
// Description: This function retrieves current platform language and stores it in
//              passed pointer
//
// Input:       CHAR8 ** Lang - pointer to where to store current language
//              BOOLEAN *Allocated - flag if memory was allocated for language
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetCurrentLanguage(
    CHAR8 ** Language,
    BOOLEAN *Allocated
)
{
    EFI_STATUS Status;
    UINTN Size = 0;

    *Allocated = FALSE;

    Status = pRS->GetVariable(L"PlatformLang", &EfiVariableGuid, NULL, &Size, *Language);
    if(Status == EFI_BUFFER_TOO_SMALL) {
        Status = pBS->AllocatePool(EfiBootServicesData, Size, Language);
        if(!EFI_ERROR(Status)) {
            Status = pRS->GetVariable(L"PlatformLang", &EfiVariableGuid, NULL, &Size, *Language);
            *Allocated = TRUE;
        }
    }
    if(EFI_ERROR(Status))
        *Language = (CHAR8 *)DefaultLanguageCode;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetLangString
//
// Description: This function reads a string from HII database with different languages
//
// Input:       IN EFI_HII_HANDLE   HiiHandle - Efi Hii Handle
//              IN STRING_REF       Token     - String Token
//              IN OUT UINTN        *StringSize - Length of the StringBuffer in bytes
//              OUT EFI_STRING      *StringBuffer - The pointer to the buffer to receive 
//                                  the characters in the string.
//
// Output:      EFI_STATUS - Depending on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetLangString(
    IN EFI_HII_HANDLE HiiHandle,
    IN EFI_STRING_ID Token,
    IN OUT UINTN *StringSize, 
    OUT EFI_STRING StringBuffer
)
{
    EFI_STATUS Status;
    EFI_HII_STRING_PROTOCOL *HiiString;
    CHAR8 *Language;
    BOOLEAN Allocated;
    
    Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &HiiString);
    if(EFI_ERROR(Status))
        return Status;

    GetCurrentLanguage(&Language, &Allocated);
    
    Status = HiiString->GetString(HiiString, Language, HiiHandle, Token, StringBuffer, StringSize, NULL);
    if(Status == EFI_INVALID_LANGUAGE) {
        if(Allocated)
            Status = HiiString->GetString(HiiString, (CHAR8 *)DefaultLanguageCode, HiiHandle, Token, StringBuffer, StringSize, NULL);
    }

    if(Status == EFI_INVALID_LANGUAGE)
        Status = HiiString->GetString(HiiString, LANGUAGE_CODE_ENGLISH, HiiHandle, Token, StringBuffer, StringSize, NULL);

    if(Allocated)
        pBS->FreePool(Language);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetUniString
//
// Description: This function reads a string from HII database
//
// Input:       IN EFI_HII_HANDLE   HiiHandle - Efi Hii Handle
//              IN STRING_REF       Token     - String Token
//              IN OUT UINTN        *StringSize - Length of the StringBuffer in bytes
//              OUT EFI_STRING      *StringBuffer - The pointer to the buffer to receive 
//                                  the characters in the string.
//
// Output:      EFI_STATUS - Depending on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetUniString(
    IN EFI_HII_HANDLE HiiHandle,
    IN EFI_STRING_ID Token,
    IN OUT UINTN *StringSize, 
    OUT EFI_STRING *StringBuffer
)
{
    EFI_STATUS Status;
    
    if (*StringBuffer == NULL) 
        *StringSize = 0;      //reset size if buffer is NULL


    Status = GetLangString(HiiHandle, Token, StringSize, *StringBuffer);
    if(Status == EFI_BUFFER_TOO_SMALL) {
         Status = pBS->AllocatePool(EfiBootServicesData, *StringSize, StringBuffer);
         if(!EFI_ERROR(Status))
            Status = GetLangString(HiiHandle, Token, StringSize, *StringBuffer);
    }

    if(EFI_ERROR(Status))
        *StringBuffer = NULL;

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    CsmOptOutLaunchCallback
//
// Description:  This function checks if CSM can be disabled in current boot
//
//  Input:
// 	IN EFI_HII_HANDLE HiiHandle - HII handle of formset
//  IN UINT16 Class - class of formset
//  IN UINT16 SubClass - subclass of formset
//  IN UINT16 Key - Id of setup control
//
//  Output:
//  EF_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CsmOptOutLaunchCallback(
    IN EFI_HII_HANDLE HiiHandle,
    IN UINT16 Class,
    IN UINT16 SubClass,
    IN UINT16 Key
)
{
    EFI_STATUS Status;
    UINT8 MsgKey;
    EFI_BROWSER_ACTION_REQUEST *rq;
    EFI_STRING Title = NULL;
    EFI_STRING Message = NULL;
    UINTN Size;


    CALLBACK_PARAMETERS *Callback = NULL;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return EFI_UNSUPPORTED;

    rq = Callback->ActionRequest;
    *rq = EFI_BROWSER_ACTION_REQUEST_NONE;

    if(Callback->Value->u8 == 0) {
    /* trying to disable CSM */
        if(IsLegacyVideo()) {
            if(AmiPostMgr == NULL)
                Status = pBS->LocateProtocol(&AmiPostManagerProtocolGuid, NULL, &AmiPostMgr);
                if(EFI_ERROR(Status))
                    return Status;
            GetUniString(HiiHandle, STRING_TOKEN(STR_LEGACY_VIDEO_MSGBOX_TITLE), &Size, &Title);
            GetUniString(HiiHandle, STRING_TOKEN(STR_LEGACY_VIDEO_MSGBOX_MESSAGE), &Size, &Message);
            
            Status = AmiPostMgr->DisplayMsgBox((Title == NULL)? L" Warning " : Title,
                                               (Message == NULL)? L"Video is in Legacy mode. Select Video policy UEFI only, reboot and try again" : Message,
                                               MSGBOX_TYPE_OK,
                                               &MsgKey);
            return EFI_UNSUPPORTED;
        }
    }
    return EFI_SUCCESS;
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
