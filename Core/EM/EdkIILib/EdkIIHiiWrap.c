//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Core/EdkIICompLib/EdkIIHiiWrap.c 2     5/13/11 6:17p Artems $
//
// $Revision: 2 $
//
// $Date: 5/13/11 6:17p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EdkIICompLib/EdkIIHiiWrap.c $
// 
// 2     5/13/11 6:17p Artems
// Bugfix: avoid using uninitialized pointer
// 
// 1     5/05/11 5:06p Artems
// EdkII compatibility library
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  EdkIIHiiWrap.c
//
//  Description:
//  
//
//<AMI_FHDR_END>
//*************************************************************************

#include <AmiDxeLib.h>
#include <EdkIIHii.h>
#include <Protocol/HiiString.h>


static EFI_HII_STRING_PROTOCOL *HiiString = NULL;
static EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;


EFI_STRING HiiGetString(
    IN EFI_HII_HANDLE  HiiHandle,
    IN EFI_STRING_ID   StringId,
    IN CONST CHAR8     *Language  OPTIONAL)
{
    EFI_STRING String = NULL;
    UINTN StringSize = 0;
    EFI_STATUS Status;
    CHAR8* PlatformLang = NULL;
    UINTN Size = 0;

    if(HiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status))
            return NULL;
    }

    if(Language != NULL) {
        Status = HiiString->GetString(HiiString, Language, HiiHandle, StringId, String, &StringSize, NULL);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, StringSize, &String);
            if(!EFI_ERROR(Status))
                Status = HiiString->GetString(HiiString, Language, HiiHandle, StringId, String, &StringSize, NULL);
        }
        if(EFI_ERROR(Status) && Status != EFI_INVALID_LANGUAGE)
            return NULL;            //string not found
    }

//language not provided - try platform language
    Status = GetEfiVariable(L"PlatformLang", &EfiVariableGuid, NULL, &Size, &PlatformLang);
    if(!EFI_ERROR(Status)) {
        Status = HiiString->GetString(HiiString, PlatformLang, HiiHandle, StringId, String, &StringSize, NULL);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, StringSize, &String);
            if(!EFI_ERROR(Status))
                Status = HiiString->GetString(HiiString, PlatformLang, HiiHandle, StringId, String, &StringSize, NULL);
        }
        pBS->FreePool(PlatformLang);
    }
    return (EFI_ERROR(Status)) ? NULL : String;
}


EFI_STRING_ID HiiSetString(
    IN EFI_HII_HANDLE HiiHandle,
    IN EFI_STRING_ID  StringId,            OPTIONAL
    IN EFI_STRING     String,
    IN CHAR8          *SupportedLanguages  OPTIONAL)
{
    EFI_STATUS Status;
    CHAR8* Languages = NULL;
    UINTN LangSize = 0;
    CHAR8* CurrentLanguage;
    BOOLEAN LastLanguage = FALSE;

    if(HiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status))
            return 0;
    }

    if(SupportedLanguages == NULL) {
        Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, LangSize, &Languages);
            if(EFI_ERROR(Status))
                return NULL;        //not enough resources to allocate string
            Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
        }
        if(EFI_ERROR(Status))
            return 0;
    } else {
        Languages = SupportedLanguages;
     }

    while(!LastLanguage) {
        CurrentLanguage = Languages;        //point CurrentLanguage to start of new language
        while(*Languages != ';' && *Languages != 0)
            Languages++;

        if(*Languages == 0) {       //last language in language list
            LastLanguage = TRUE;
            if(StringId == 0)
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            else
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            if(EFI_ERROR(Status))
                return 0;
        } else {
            *Languages = 0;         //put null-terminator
            if(StringId == 0)
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            else
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            *Languages = ';';       //restore original character
            Languages++;
            if(EFI_ERROR(Status))
                return 0;
        }
    }
    return StringId;        
}

/*
UINT8* HiiCreateActionOpCode(
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN EFI_STRING_ID    QuestionConfig)
{
    return NULL;
}

UINT8* HiiCreateGotoOpCode(
    IN VOID             *OpCodeHandle,
    IN EFI_FORM_ID      FormId,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN EFI_QUESTION_ID  QuestionId)
{
    return NULL;
}

UINT8* HiiCreateGuidOpCode (
    IN VOID            *OpCodeHandle,
    IN CONST EFI_GUID  *Guid,
    IN CONST VOID      *GuidOpCode,    OPTIONAL
    IN UINTN           OpCodeSize)
{
    return NULL;
}


EFI_STATUS HiiUpdateForm(
    IN EFI_HII_HANDLE  HiiHandle,           
    IN EFI_GUID        *FormSetGuid,        OPTIONAL
    IN EFI_FORM_ID     FormId,
    IN VOID            *StartOpCodeHandle,
    IN VOID            *EndOpCodeHandle     OPTIONAL)
{
    return EFI_UNSUPPORTED;
}

VOID* HiiAllocateOpCodeHandle(
    VOID)
{
    return NULL;
}

VOID HiiFreeOpCodeHandle(
    VOID  *OpCodeHandle)
{
    return;
}   

EFI_HII_HANDLE HiiAddPackages(
    IN CONST EFI_GUID    *PackageListGuid,
    IN       EFI_HANDLE  DeviceHandle  OPTIONAL,
    ...)
{
    return NULL;
}   
*/



//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
