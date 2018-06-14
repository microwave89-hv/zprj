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


//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiiString.c 7     8/15/12 3:45p Artems $
//
// $Revision: 7 $
//
// $Date: 8/15/12 3:45p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiiString.c $
// 
// 7     8/15/12 3:45p Artems
// [TAG]  		EIP96755
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Strings in new language added at runtime lost during export
// [RootCause]  	Every language represented by its own string package.
// When 
// strings of new language added at runtime, they're added to database,
// but not to the list of packages. Export function is working with 
// list of packages, so new language strings will be missed
// [Solution]  	Added code to create new string package at runtime when
// new string
// of new language is added to database
// [Files]  		HiiPrivate.h HiiString.c
// 
// 6     5/22/12 4:34p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio
// [Files]  		HiiDatabase.c HiiFont.c HiiFontEx.c HiiPrivate.h HiiString.c
// UefiHii.h
// 
// 
// 5     10/24/11 5:40p Artems
// EIP 70530: Bug reported by SCT 2.3.1. Languages shold be compared
// ignoring case
// 
// 4     5/13/11 6:15p Artems
// Renamed functions HiiGetString and HiiSetString to AmiHiiGetString and
// AmiHiiSetString 
// to avoid collusion with EdkII native library functions
// 
// 3     12/03/09 12:02p Aaronp
// Fix for SCT GetSecondLanguages failures.  
// 
// 2     11/23/09 7:38p Felixp
// HiiGetLanguages is updated to accept NULL language buffer when
// *LanguagesSize is zero.
// 
// 1     10/09/09 6:12p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	HiiString.c
//
// Description:	Hii string protocol functions implementation
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#pragma warning (disable : 4090)

#include <AmiDxeLib.h>
#include "HiiPrivate.h"

#define DEFAULT_FONT    0x100
#define INVALID_FONT_ID 0xFEFE

extern HII_DATABASE_PRIVATE_DATA PrivateData;

DBE_OFFSET_KEY_CONTEXT StringDbKeyContext = {EFI_FIELD_OFFSET(STRING_RECORD ,StringId), 4 };
DBE_KEY_FIELD		  StringDbKeyField   = OFFSET_KEY(StringDbKeyContext);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AmiHiiGetString
//
//  Description:
//  This function is HII String protocol function GetString implementation 
//
//  Input:
// 	IN EFI_HII_STRING_PROTOCOL *This - Pointer to EFI_HII_STRING_PROTOCOL structure
// 	IN CHAR8 *Language - Language definition
//  IN EFI_HII_HANDLE PackageList - Handle of package list
//  IN EFI_STRING_ID StringId - String Id
//  OUT EFI_STRING String - Pointer to output string
//  IN OUT UINTN *StringSize - Pointer to string size value
//  OUT EFI_FONT_INFO *StringFontInfo - Pointer to returned string font info
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - String or StringSize or Language is NULL
//  EFI_NOT_FOUND - String not found
//  EFI_BUFFER_TOO_SMALL - Allocated buffer too small
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiHiiGetString(
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN CONST CHAR8					 *Language,
	IN EFI_HII_HANDLE				 PackageList,
	IN EFI_STRING_ID				 StringId,
	OUT EFI_STRING					 String,
	IN OUT UINTN					 *StringSize,
	OUT EFI_FONT_INFO				 **StringFontInfo OPTIONAL)
{
	PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *)PackageList;
	STRING_RECORD DbKey;
	INT8 Vicinity;
	STRING_RECORD *Found;
    UINTN *FindRecord;
	UINT32 Size;
	EFI_STATUS Status;
	LANGUAGE_LINK *Ptr;
	UINT32 i;
	UINT16 SaveLanguage;

    if (Language == NULL || StringId < 1 || StringSize == NULL || PackageList == NULL)
        return EFI_INVALID_PARAMETER;

    if (String == NULL && *StringSize != 0)
        return EFI_INVALID_PARAMETER;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;

	DbKey.StringId = StringId;
	Status = GetLanguageId(Record, Language, &(DbKey.LanguageId), &Ptr);
	if(EFI_ERROR(Status))
		return EFI_INVALID_LANGUAGE;

	Status = DbeLocateKey(&(Record->StringDb), 0, &DbKey, &FindRecord, &Vicinity, NULL);
	if(EFI_ERROR(Status))
    {
        //string not found in database, try different languages
		SaveLanguage = DbKey.LanguageId;
		for(i = 0; i < Record->LanguageList.Size; i++)
		{
			if (i == SaveLanguage)
				continue;
			DbKey.LanguageId = (UINT16)i;
			Status = DbeLocateKey(&(Record->StringDb), 0, &DbKey, &FindRecord, &Vicinity, NULL);
			if(!EFI_ERROR(Status))
				return EFI_INVALID_LANGUAGE;    //string exists but with different language
		}
		
		return EFI_NOT_FOUND;
    }

    Found = (STRING_RECORD *)(UINTN)(*FindRecord);

	Size = StrSize16(Found->String);
    
	if(Size > *StringSize)
	{
		*StringSize = Size;
		return EFI_BUFFER_TOO_SMALL;
	}

	StrCpy16(String, Found->String);
	*StringSize = Size;

    if(StringFontInfo != NULL)
        Status = FindStingFontInfoById(Record, Found->FontId, StringFontInfo);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AmiHiiSetString
//
//  Description:
//  This function is HII String protocol function SetString implementation 
//
//  Input:
// 	IN EFI_HII_STRING_PROTOCOL *This - Pointer to EFI_HII_STRING_PROTOCOL structure
//  IN EFI_HII_HANDLE PackageList - Handle of package list
//  IN EFI_STRING_ID StringId - String Id
// 	IN CHAR8 *Language - Language definition
//  IN EFI_STRING String - String to set
//  IN EFI_FONT_INFO *StringFontInfo - Pointer to string font info
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - String or Language is NULL
//  EFI_NOT_FOUND - String not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiHiiSetString (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN EFI_STRING_ID				 StringId,
	IN CONST CHAR8					 *Language,
	IN CONST EFI_STRING				 String,
	IN CONST EFI_FONT_INFO			 *StringFontInfo OPTIONAL)
{
	PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *)PackageList;
	STRING_RECORD DbKey;
	INT8 Vicinity;
	STRING_RECORD *Found;
    UINTN *FindRecord;
	UINT32 i;
	UINT16 SaveLanguage;
	LANGUAGE_LINK *Ptr;
	EFI_STATUS Status;

	if(String == NULL || Language == NULL || PackageList == NULL)
		return EFI_INVALID_PARAMETER;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;

	DbKey.StringId = StringId;
	Status = GetLanguageId(Record, Language, &(DbKey.LanguageId), &Ptr);

	if(EFI_ERROR(Status))
		return Status;

	Status = DbeLocateKey(&(Record->StringDb), 0, &DbKey, &FindRecord, &Vicinity, NULL);
	if(!EFI_ERROR(Status))
	{	//updated string found in database - retreive font info
        Found = (STRING_RECORD *)(UINTN)(*FindRecord);
		DbKey.FontId = Found->FontId;
		DbeDelete(&(Record->StringDb), Found, TRUE);
	}
	else //try same StringId with different languages
	{
		SaveLanguage = DbKey.LanguageId;
		for(i = 0; i < Record->LanguageList.Size; i++)
		{
			if (i == SaveLanguage)
				continue;
			DbKey.LanguageId = i;
			Status = DbeLocateKey(&(Record->StringDb), 0, &DbKey, &FindRecord, &Vicinity, NULL);
			if(!EFI_ERROR(Status))
				break;
		}
		if(i == Record->LanguageList.Size)
			return EFI_NOT_FOUND;

        Found = (STRING_RECORD *)(UINTN)(*FindRecord);
		DbKey.FontId = Found->FontId;
		DbKey.LanguageId = SaveLanguage;
	}

    if(StringFontInfo != NULL) {
        Status = FindStringFontInfoByTemplate(Record, StringFontInfo, &DbKey.FontId);
        if(EFI_ERROR(Status)) {
            Status = AddStringFont(Record, INVALID_FONT_ID, StringFontInfo->FontSize,
                                   StringFontInfo->FontStyle, StringFontInfo->FontName, &DbKey.FontId);
            if(EFI_ERROR(Status))
                return Status;
        }
            
    }

	Status = AddString(Record, DbKey.LanguageId, DbKey.StringId, DbKey.FontId, String);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiNewString
//
//  Description:
//  This function is HII String protocol function NewString implementation 
//
//  Input:
// 	IN EFI_HII_STRING_PROTOCOL *This - Pointer to EFI_HII_STRING_PROTOCOL structure
//  IN EFI_HII_HANDLE PackageList - Handle of package list
//  OUT EFI_STRING_ID *StringId - Pointer to returned string Id
// 	IN CHAR8 *Language - Language definition
// 	IN CHAR16 *LanguageName - Language human readable name
//  IN EFI_STRING String - String to set
//  IN EFI_FONT_INFO *StringFontInfo - Pointer to string font info
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - String or Language or StringId is NULL
//  EFI_NOT_FOUND - Package list handle is invalid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiNewString (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	OUT EFI_STRING_ID				 *StringId,
	IN CONST CHAR8					 *Language,
	IN CONST CHAR16					 *LanguageName OPTIONAL,
	IN CONST EFI_STRING				 String,
	IN CONST EFI_FONT_INFO			 *StringFontInfo)
{
	PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *)PackageList;
	EFI_STATUS Status;
	UINT16 LanguageId;
	LANGUAGE_LINK *Link;
    UINT16 FontId;
    CHAR16 DefaultName[80];

	if(String == NULL || StringId == NULL || Language == NULL || PackageList == NULL)
		return EFI_INVALID_PARAMETER;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;

	Status = GetLanguageId(Record, Language, &LanguageId, &Link);
	if(EFI_ERROR(Status))
	{
		Status = AddLanguage(Record, Language, LanguageName, 0);
		if(EFI_ERROR(Status))
			return Status;
		Status = GetLanguageId(Record, Language, &LanguageId, &Link);
        //language added, now add language name string to database
        if(LanguageName == NULL) {
            CreateLanguageName(Language, DefaultName, 80 * sizeof(CHAR16));
            LanguageName = DefaultName;
        }
        //at this point LastStringId has value LanguageName + 1
        Status = AmiHiiSetString(This, PackageList, Link->LastStringId - 1, Language, LanguageName, NULL);
	}

    if(StringFontInfo != NULL) {
        Status = FindStringFontInfoByTemplate(Record, StringFontInfo, &FontId);
        if(EFI_ERROR(Status)) {
            Status = AddStringFont(Record, INVALID_FONT_ID, StringFontInfo->FontSize,
                                   StringFontInfo->FontStyle, StringFontInfo->FontName, &FontId);
            if(EFI_ERROR(Status))
                return Status;
        }
            
    } else {
        FontId = DEFAULT_FONT;
    }

	Status = AddString(Record, LanguageId, Link->LastStringId, FontId, String);
	if(EFI_ERROR(Status))
		return Status;

    *StringId = Link->LastStringId;

	Link->LastStringId++;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiGetLanguages
//
//  Description:
//  This function is HII String protocol function GetLanguages implementation 
//
//  Input:
// 	IN EFI_HII_STRING_PROTOCOL *This - Pointer to EFI_HII_STRING_PROTOCOL structure
//  IN EFI_HII_HANDLE PackageList - Handle of package list
// 	IN OUT CHAR8 *Languages - Pointer to returned language buffer
//  IN OUT UINTN *LanguagesSize - Pointer to language buffer size
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - LanguagesSize or Languages is NULL
//  EFI_NOT_FOUND - Package list handle is invalid or NULL
//  EFI_BUFFER_TOO_SMALL - Allocated buffer too small
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiGetLanguages (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN OUT CHAR8					 *Languages,
	IN OUT UINTN					 *LanguagesSize
)
{
	PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *)PackageList;
//	EFI_STATUS Status;
	LANGUAGE_LINK *Link;
    UINTN Size = 0;

    if(PackageList == NULL)
        return EFI_INVALID_PARAMETER;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;

	if(LanguagesSize == NULL || Languages == NULL && *LanguagesSize != 0)
		return EFI_INVALID_PARAMETER;

    if(Record->LanguageList.Size == 0)
    {
        *LanguagesSize = 0;
        *Languages = 0;
        return EFI_SUCCESS;
    }

    Link = (LANGUAGE_LINK *)Record->LanguageList.pHead;
    while(Link != NULL)
    {
        Size += StrSize8(Link->Language);
        Link = (LANGUAGE_LINK *)Link->Link.pNext;
    }

    if(Size > *LanguagesSize)
    {
        *LanguagesSize = Size;
        return EFI_BUFFER_TOO_SMALL;
    }

    *LanguagesSize = Size;

    Link = (LANGUAGE_LINK *)Record->LanguageList.pHead;
    while(Link != NULL)
    {
        Size = StrSize8(Link->Language);
        Size--;         //skip NULL-terminator
        MemCpy(Languages, Link->Language, Size);
        Languages += Size;                      //shift pointer
        *Languages = ';';                       //add delimiter
        Languages++;
        Link = (LANGUAGE_LINK *)Link->Link.pNext;
    }

    Languages--;            //change delimiter to NULL-terminator
    *Languages = 0;         

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiGetSecondLanguages
//
//  Description:
//  This function is HII String protocol function GetSecondaryLanguages implementation 
//
//  Input:
// 	IN EFI_HII_STRING_PROTOCOL *This - Pointer to EFI_HII_STRING_PROTOCOL structure
//  IN EFI_HII_HANDLE PackageList - Handle of package list
//  IN CHAR8 *FirstLanguage - First language definition
// 	IN OUT CHAR8 *Languages - Pointer to returned language buffer
//  IN OUT UINTN *LanguagesSize - Pointer to language buffer size
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - LanguagesSize or Languages is NULL
//  EFI_NOT_FOUND - Package list handle is invalid or NULL
//  EFI_BUFFER_TOO_SMALL - Allocated buffer too small
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiGetSecondLanguages(
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN CONST CHAR8					 *FirstLanguage,
	IN OUT CHAR8					 *SecondLanguages,
	IN OUT UINTN					 *SecondLanguagesSize
)
{
    EFI_STATUS Status;
    UINTN Size = 0;
    UINTN i = 0;

    CHAR8 *Langs = NULL;

    if(FirstLanguage == NULL || SecondLanguages == NULL || SecondLanguagesSize == NULL)
        return EFI_INVALID_PARAMETER;

    // Get the size of all the languages in the Hii Package
    Status = HiiGetLanguages(This, PackageList, NULL, &Size);

    if(EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL)
        return Status;

    // Allocate space for the languages
    Status = pBS->AllocatePool(EfiBootServicesData, Size, &Langs);

    if(!EFI_ERROR(Status))
        // Get the langues into the temp buffer
        Status = HiiGetLanguages(This, PackageList, Langs, &Size);

    // find and remove the primary language from the string
    if(!EFI_ERROR(Status))
    {
        Status = EFI_INVALID_LANGUAGE;

        for(; i < Size; i++)
        {
            // check if the current offset matches the first language
            if(MemCmp(Langs+i,FirstLanguage,StrSize8(FirstLanguage)-1) == 0)
            {
                Status = EFI_SUCCESS;

                // copy the rest of the string on top of the primary strings location
                pBS->CopyMem(Langs+i,Langs+i+StrSize8(FirstLanguage),StrSize8(Langs)-i-StrSize8(FirstLanguage));
                break;
            }
        }
    }

    if(!EFI_ERROR(Status))
    {
        Status = EFI_BUFFER_TOO_SMALL;

        // Check if the buffer is large enough to fit the secondary langues
        if(*SecondLanguagesSize >= StrSize8(Langs))
        {
            Status = EFI_SUCCESS;
            MemCpy(SecondLanguages, Langs, StrSize8(Langs));
        }

        // fill in the size of the secondary langauges
        *SecondLanguagesSize = StrSize8(Langs);        
    }
   
    if(Langs != NULL)
        pBS->FreePool(Langs);

    return Status;
}

// *************************** Service functions (not for public use) ************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CreateLanguageName
//
//  Description:
//  This function creates human-readable language name from RFC name
//
//  Input:
// 	IN CHAR8 *RfcName - pointer to RFC name
//  OUT CHAR16* OutName - pointer where to store human-readable name
//  UINTN MaxSize - max size of output buffer in bytes
//
//  Output:
//  UINT16 - number of strings in package
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreateLanguageName(
    IN CHAR8 *RfcName, 
    OUT CHAR16* OutName, 
    UINTN MaxSize)
{
    UINTN i;

    for(i = 0; (RfcName[i] != 0 && i < (MaxSize / 2 - 1)); i++)
        OutName[i] = RfcName[i];
    OutName[i] = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddStringPackage
//
//  Description:
//  This function creates string package for language not existed in package list
//  at the time of submission to database
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where language belongs
//  IN CHAR8 *Language - Language RFC name
//
//  Output:
//  UINT16 - number of strings in package
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 AddStringPackage(
   PACKAGE_LIST_RECORD *PackageList,
   CHAR8 *Language)
{
    UINT32 Size;
    PACKAGE_LINK *Template;
    PACKAGE_LINK *NewLink;
    DLIST *PackList;
    UINT16 LanguageStringId;
    UINT32 i;
    EFI_HII_STRING_PACKAGE_HDR *Hdr;
    EFI_HII_STRING_PACKAGE_HDR *NewHdr;

    PackList = &(PackageList->PackageList);
    Template = (PACKAGE_LINK *)PackList->pHead;
    while(Template != NULL) {
        if(Template->Package.Type == EFI_HII_PACKAGE_STRINGS)
            break;
        Template = (PACKAGE_LINK *)Template->Link.pNext;
    }

    if(Template == NULL) {//no string packages in this package list
        LanguageStringId = 1;
    } else {
        Hdr = (EFI_HII_STRING_PACKAGE_HDR *)&(Template->Package);
        LanguageStringId = Hdr->LanguageName;
    }

    Size = sizeof(EFI_HII_STRING_PACKAGE_HDR) - 1;
	Size += StrSize8(Language);

    NewLink = (PACKAGE_LINK *) CreateNewLink(Size);
    if(NewLink == NULL)
		return 0;

    NewLink->Package.Type = EFI_HII_PACKAGE_STRINGS;
    NewLink->Package.Length = Size;  //this is technically incorrect, but it will be updated upon export
    NewHdr = (EFI_HII_STRING_PACKAGE_HDR *)&(NewLink->Package);
    NewHdr->HdrSize = Size;
    NewHdr->StringInfoOffset = Size;
    if(Template == NULL) {
        for(i = 0; i < 16; i++)
            NewHdr->LanguageWindow[i] = 0;
    } else {
        for(i = 0; i < 16; i++)
            NewHdr->LanguageWindow[i] = Hdr->LanguageWindow[i];
    }
    NewHdr->LanguageName = LanguageStringId;
    StrCpy8(NewHdr->Language, Language);
    DListAdd(PackList, (DLINK *)NewLink);
    return LanguageStringId + 1;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddLanguage
//
//  Description:
//  This function adds language to private HII database 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where language belongs
//  IN EFI_HII_HANDLE PackageList - Handle of package list
//  IN CHAR8 *Language - Language Id
// 	IN CHAR16 *LanguageName - Pointer to human readable language name
//  IN UINT16 LastStringId - Last string Id on this language
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddLanguage(
   PACKAGE_LIST_RECORD *PackageList,
   CHAR8 *Language,
   CHAR16* LanguageName,
   UINT16 LastStringId)
{
	UINT32 Size1, Size2 = 0;
	LANGUAGE_LINK *Link;
    CHAR16 DefaultName[80];
    UINT8 *Ptr;

	Size1 = StrSize8(Language);

	if(LanguageName == NULL) {
        CreateLanguageName(Language, DefaultName, 80 * sizeof(CHAR16));
        LanguageName = DefaultName;
    }

    Size2 = StrSize16(LanguageName);

	Link = (LANGUAGE_LINK *)CreateNewLink(Size1 + Size2 + sizeof(UINT32));
	if(Link == NULL)
		return EFI_OUT_OF_RESOURCES;

    if(LastStringId != 0) {
        Link->LastStringId = LastStringId;
    } else {
    //we're adding language, that wasn't in package list from the start
        Link->LastStringId = AddStringPackage(PackageList, Language);
        if(Link->LastStringId == 0)
            return EFI_OUT_OF_RESOURCES;
    }	
	StrCpy8(Link->Language, Language);

	Ptr = (UINT8 *)Link->Language;
	Ptr += Size1;
    StrCpy16((CHAR16 *)Ptr, LanguageName);

	DListAdd(&(PackageList->LanguageList), (DLINK *)Link);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetLanguageId
//
//  Description:
//  This function returns language private Id which corresponds with given language Id 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where language belongs
//  IN CHAR8 *Language - Language Id
// 	OUT UINT16 *LanguageId - Pointer where to return private Id
//  OUT LANGUAGE_LINK **Found - Pointer where to return found language private data
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_NOT_FOUND - language not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetLanguageId(
   PACKAGE_LIST_RECORD *PackageList,
   CHAR8 *Language,
   UINT16 *LanguageId,
   LANGUAGE_LINK **Found OPTIONAL)
{
	LANGUAGE_LINK *Link = (LANGUAGE_LINK *)PackageList->LanguageList.pHead;
	UINT8 Id;

	Id = 0;
	while(Link != NULL)
	{
		if(LanguageCodesEqual(Language, Link->Language))
		{
			*LanguageId = Id;

            if(Found)
			    *Found = Link;

			return EFI_SUCCESS;
		}
		Link = (LANGUAGE_LINK *)Link->Link.pNext;
		Id++;
	}
	return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddString
//
//  Description:
//  This function adds string to private storage 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where string belongs
// 	IN UINT16 LanguageId - Private language Id of the string
// 	IN UINT16 StringId - Private string Id of the string
// 	IN UINT16 FontId - Private font Id of the string
// 	IN EFI_STRING String - String to add
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddString(
	PACKAGE_LIST_RECORD *PackageList,
	UINT16		LanguageId,
	UINT16		StringId,
	UINT16		FontId,
	EFI_STRING  String)
{
	STRING_RECORD *Record;
	UINT32 Size;
	EFI_STATUS Status;

	Size = StrSize16(String);

	Status = pBS->AllocatePool(
		                EfiBootServicesData, 
						Size + 6, 
						&Record);
	if (EFI_ERROR(Status))
		return Status;

	Record->FontId = FontId;
	Record->LanguageId = LanguageId;
	Record->StringId = StringId;
	StrCpy16(Record->String, String);

	DbeInsert(&(PackageList->StringDb), Record);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ParseStringsPackage
//
//  Description:
//  This function parses string package 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where string package belongs
// 	IN EFI_HII_STRING_PACKAGE_HDR *Package - Pointer to package to parse
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_ERROR - Some error occured during execution
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseStringsPackage(
   PACKAGE_LIST_RECORD			 *PackageList,
   IN EFI_HII_STRING_PACKAGE_HDR *Package)
{
	EFI_STATUS Status;
	LANGUAGE_LINK *Link;
	UINT16 LanguageId;
	UINT16 StringId;
	UINT16 FontId;
	EFI_HII_STRING_BLOCK *ParsePointer;
	UINT16 StringCount;
	STRING_RECORD DbKey;
	INT8 Vicinity;
	STRING_RECORD *Found;
    UINTN *FindRecord;
    BOOLEAN NewLanguage = FALSE;
    CHAR16 *FontName;

	ParsePointer = (EFI_HII_STRING_BLOCK *)Package;
	(UINT8 *)ParsePointer += Package->StringInfoOffset;

	Status = GetLanguageId(PackageList, Package->Language, &LanguageId, &Link);
	if(EFI_ERROR(Status))
	{
		LanguageId = (UINT16)PackageList->LanguageList.Size;
		StringId = 1;
        NewLanguage = TRUE;
	}
	else
		StringId = Link->LastStringId;

	while(ParsePointer->BlockType != EFI_HII_SIBT_END)
	{
		switch(ParsePointer->BlockType)
		{
			case EFI_HII_SIBT_SKIP1:
				StringId += ((EFI_HII_SIBT_SKIP1_BLOCK *)ParsePointer)->SkipCount;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_SKIP1_BLOCK);
				break;
			case EFI_HII_SIBT_SKIP2:
 				StringId += ((EFI_HII_SIBT_SKIP2_BLOCK *)ParsePointer)->SkipCount;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_SKIP2_BLOCK);
				break;
			case EFI_HII_SIBT_EXT1:
				(UINT8 *)ParsePointer += ((EFI_HII_SIBT_EXT1_BLOCK *)ParsePointer)->Length;
				break;
			case EFI_HII_SIBT_EXT2:
				(UINT8 *)ParsePointer += ((EFI_HII_SIBT_EXT2_BLOCK *)ParsePointer)->Length;
				break;
			case EFI_HII_SIBT_EXT4:
				(UINT8 *)ParsePointer += ((EFI_HII_SIBT_EXT4_BLOCK *)ParsePointer)->Length;
				break;
			case EFI_HII_SIBT_FONT:
                FontName = (CHAR16 *)((EFI_HII_SIBT_FONT_BLOCK *)ParsePointer + 1);
                Status = AddStringFont(PackageList,
                                       ((EFI_HII_SIBT_FONT_BLOCK *)ParsePointer)->FontId,
                                       ((EFI_HII_SIBT_FONT_BLOCK *)ParsePointer)->FontSize,
                                       ((EFI_HII_SIBT_FONT_BLOCK *)ParsePointer)->FontStyle,
                                       FontName, NULL);
                if(EFI_ERROR(Status))
                    return Status;
				(UINT8 *)ParsePointer += ((EFI_HII_SIBT_FONT_BLOCK *)ParsePointer)->Header.Length;
				break;
			case EFI_HII_SIBT_STRING_SCSU:
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRING_SCSU_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, DEFAULT_FONT,
										1, TRUE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
				break;
			case EFI_HII_SIBT_STRING_SCSU_FONT:
				FontId = ((EFI_HII_SIBT_STRING_SCSU_FONT_BLOCK *)ParsePointer)->FontIdentifier;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRING_SCSU_FONT_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, FontId,
										1, TRUE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
				break;
			case EFI_HII_SIBT_STRINGS_SCSU:
				StringCount = ((EFI_HII_SIBT_STRINGS_SCSU_BLOCK *)ParsePointer)->StringCount;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRINGS_SCSU_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, DEFAULT_FONT,
										StringCount, TRUE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
				break;
			case EFI_HII_SIBT_STRINGS_SCSU_FONT:
				StringCount = ((EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK *)ParsePointer)->StringCount;
				FontId = ((EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK *)ParsePointer)->FontIdentifier;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, FontId,
										StringCount, TRUE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
			case EFI_HII_SIBT_STRING_UCS2:
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRING_UCS2_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, DEFAULT_FONT,
										1, FALSE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
				break;
			case EFI_HII_SIBT_STRING_UCS2_FONT:
				FontId = ((EFI_HII_SIBT_STRING_UCS2_FONT_BLOCK *)ParsePointer)->FontIdentifier;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRING_UCS2_FONT_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, FontId,
										1, FALSE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
				break;
			case EFI_HII_SIBT_STRINGS_UCS2:
				StringCount = ((EFI_HII_SIBT_STRINGS_UCS2_BLOCK *)ParsePointer)->StringCount;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRINGS_UCS2_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, DEFAULT_FONT,
										StringCount, FALSE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
				break;
			case EFI_HII_SIBT_STRINGS_UCS2_FONT:
				StringCount = ((EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK *)ParsePointer)->StringCount;
				FontId = ((EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK *)ParsePointer)->FontIdentifier;
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK);
				Status = ExtractStrings(PackageList, LanguageId, &StringId, FontId,
										StringCount, TRUE, &ParsePointer);
				if(EFI_ERROR(Status))
					return Status;
			case EFI_HII_SIBT_DUPLICATE:
				DbKey.LanguageId = LanguageId;
				DbKey.StringId = ((EFI_HII_SIBT_DUPLICATE_BLOCK *)ParsePointer)->StringId;
				Status = DbeLocateKey(&(PackageList->StringDb), 0, &DbKey, &FindRecord, &Vicinity, NULL);
				if(!EFI_ERROR(Status))
				{
                    Found = (STRING_RECORD *)(UINTN)(*FindRecord);
					Status = AddString(PackageList, Found->LanguageId, StringId, Found->FontId, Found->String);
					if(EFI_ERROR(Status))
						return Status;
					StringId++;
				}
				(UINT8 *)ParsePointer += sizeof(EFI_HII_SIBT_DUPLICATE_BLOCK);
				break;
			default:
				break;
		}
	}

//Reconstruct full language name

    if(NewLanguage)
    {
		DbKey.LanguageId = LanguageId;
		DbKey.StringId = Package->LanguageName;
        Status = DbeLocateKey(&(PackageList->StringDb), 0, &DbKey, &FindRecord, &Vicinity, NULL);

        if(!EFI_ERROR(Status))
        {
            Found = (STRING_RECORD *)(UINTN)(*FindRecord);
            Status = AddLanguage(PackageList, Package->Language, Found->String, StringId);
        }
        else
            Status = AddLanguage(PackageList, Package->Language, NULL, StringId);

        if(EFI_ERROR(Status))
            return Status;
    }
    else
	    Link->LastStringId = StringId;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ExtractStrings
//
//  Description:
//  This function extracts strings from given block of strings 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where strings belong
// 	IN UINT16 LanguageId - Private language Id
// 	IN OUT UINT16 *StringId - Pointer to string Id
// 	IN UINT16 FontId - Font Id
// 	IN UINT16 StringCount - Number of strings to extract
// 	IN BOOLEAN Compressed - Flag, that determines whether string is compressed or not
// 	IN OUT VOID **StringBlock - Pointer to block of strings to extract
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_ERROR - Some error occured during execution
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ExtractStrings(
	PACKAGE_LIST_RECORD *PackageList,
	UINT16		LanguageId,
	UINT16		*StringId,
	UINT16		FontId,
	UINT16		StringCount,
	BOOLEAN		Compressed,
	VOID		**StringBlock
)
{
	UINT16 i;
	EFI_STATUS Status;
	UINT32 StringSize;
	UINT32 MaxSize = 0x100;
	CHAR16 *String = NULL;
	VOID *Pointer = *StringBlock;

	if(Compressed)
	{
		Status = pBS->AllocatePool(
								EfiBootServicesData, 
								sizeof(CHAR16) * MaxSize, 
								&String);
		if(EFI_ERROR(Status))
			return Status;
	}

	for(i = 0; i < StringCount; i++)
	{
		if(Compressed)
		{
			StringSize = StrSize8((CHAR8 *)Pointer);
			if(StringSize > MaxSize)
			{
				MaxSize = StringSize;
				pBS->FreePool(String);
				Status = pBS->AllocatePool(
								EfiBootServicesData, 
								sizeof(CHAR16) * MaxSize, 
								&String);
				if(EFI_ERROR(Status))
					return Status;
			}
//			UncompressString(String, (CHAR8 *)Pointer);
			Status = AddString(PackageList, LanguageId, *StringId, FontId, String);
		}
		else
		{
			StringSize = StrSize16(Pointer);
			Status = AddString(PackageList, LanguageId, *StringId, FontId, (EFI_STRING)Pointer);
		}

		if(EFI_ERROR(Status))
			return Status;
		(*StringId)++;
		(UINT8 *)Pointer += StringSize;
	}
	*StringBlock = Pointer;
	if(String != NULL)
		pBS->FreePool(String);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetStringBlockSize
//
//  Description:
//  This function determines block size needed to pack strings into string package 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where strings belong
// 	IN CHAR8 *Language - Language Id
//
//  Output:
//  UINTN - String block size in bytes
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetStringBlockSize(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN CHAR8 *Language)
{
	STRING_RECORD DbKey;
	INT8 Vicinity;
	STRING_RECORD *Found;
    UINTN *FindRecord;
    EFI_STATUS Status;
    UINTN RecordIndex;
    DBE_DATABASE *Database = &(PackageList->StringDb);
    UINT16 StringCounter = 0;
    UINT16 SkipBlock = 0; //number of skip blocks to add to string block
    UINT16 CurrentStringId;
    UINTN Size = 0;
    UINTN i;

    Status = GetLanguageId(PackageList, Language, &(DbKey.LanguageId), NULL);
    if(EFI_ERROR(Status))
        return 0;

    DbKey.StringId = 1;     //find first string with given language
    Status = DbeLocateKey(&(PackageList->StringDb), 0, &DbKey, &FindRecord, &Vicinity, &RecordIndex);
    Found = (STRING_RECORD *)(UINTN)(*FindRecord);
    if(EFI_ERROR(Status))
    {   //there isn't string with string id = 1
        if(Found->LanguageId != DbKey.LanguageId) //we got string from previous language
        {
            RecordIndex++;
            Status = DbeGoToIndex(&(PackageList->StringDb), 0, RecordIndex, &Found);
        }
        SkipBlock++;    //at least one skip block should be added as far as we don't have string with id=1
    }
    CurrentStringId = Found->StringId;
    Size += StrSize16(Found->String);
    StringCounter++;

    for(i = RecordIndex + 1; 
        (i < PackageList->StringDb.RecordCount) && (Found->LanguageId == DbKey.LanguageId);
        i++)
    {
        Status = DbeGoToIndex(&(PackageList->StringDb), 0, i, &Found);
        Size += StrSize16(Found->String);
        StringCounter++;
        if(Found->StringId > (CurrentStringId + 1))
            SkipBlock++;
        CurrentStringId = Found->StringId;
    }

    Size += SkipBlock * sizeof(EFI_HII_SIBT_SKIP2_BLOCK);
    Size += StringCounter * sizeof(EFI_HII_SIBT_STRING_UCS2_BLOCK);
    Size += sizeof(EFI_HII_SIBT_END_BLOCK);

    return Size;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetStringBlock
//
//  Description:
//  This function packs strings from private storage into string package format 
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - Pointer to package list where strings belong
// 	IN CHAR8 *Language - Language Id
// 	OUT UINT8 *Buffer - Pointer to output buffer
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetStringBlock(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN CHAR8 *Language,
    IN UINT8 *Buffer)
{
	STRING_RECORD DbKey;
	INT8 Vicinity;
	STRING_RECORD *Found;
    UINTN *FindRecord;
    EFI_STATUS Status;
    UINTN RecordIndex;
    DBE_DATABASE *Database = &(PackageList->StringDb);
    UINT16 StringCounter = 0;
    UINT16 SkipBlock = 0; //number of skip blocks to add to string block
    UINT16 CurrentStringId = 1;
    UINTN Size = 0;
    UINTN i;

    Status = GetLanguageId(PackageList, Language, &(DbKey.LanguageId), NULL);

    DbKey.StringId = 1;     //find first string with given language
    Status = DbeLocateKey(&(PackageList->StringDb), 0, &DbKey, &FindRecord, &Vicinity, &RecordIndex);
    Found = (STRING_RECORD *)(UINTN)(*FindRecord);
    if(EFI_ERROR(Status))
    {   //there isn't string with string id = 1
        if(Found->LanguageId != DbKey.LanguageId) //we got string from previous language
        {
            RecordIndex++;
            Status = DbeGoToIndex(&(PackageList->StringDb), 0, RecordIndex, &Found);
        }

        ((EFI_HII_SIBT_SKIP2_BLOCK *)Buffer)->SkipCount = Found->StringId - CurrentStringId - 1;
        ((EFI_HII_SIBT_SKIP2_BLOCK *)Buffer)->Header.BlockType = EFI_HII_SIBT_SKIP2;
        Buffer += sizeof(EFI_HII_SIBT_SKIP2_BLOCK);
    }
    CurrentStringId = Found->StringId;
    ((EFI_HII_SIBT_STRING_UCS2_BLOCK *)Buffer)->Header.BlockType = EFI_HII_SIBT_STRING_UCS2;
    Buffer += sizeof(EFI_HII_SIBT_STRING_UCS2_BLOCK);
    Size = StrSize16(Found->String);
    StrCpy16((CHAR16 *)Buffer, Found->String);
    Buffer += Size;

    for(i = RecordIndex + 1; 
        (i < PackageList->StringDb.RecordCount) && (Found->LanguageId == DbKey.LanguageId);
        i++)
    {
        Status = DbeGoToIndex(&(PackageList->StringDb), 0, i, &Found);

        if(Found->StringId > (CurrentStringId + 1))       //add skip block
        {
            ((EFI_HII_SIBT_SKIP2_BLOCK *)Buffer)->SkipCount = Found->StringId - CurrentStringId - 1;
            ((EFI_HII_SIBT_SKIP2_BLOCK *)Buffer)->Header.BlockType = EFI_HII_SIBT_SKIP2;
            Buffer += sizeof(EFI_HII_SIBT_SKIP2_BLOCK);
        }

        ((EFI_HII_SIBT_STRING_UCS2_BLOCK *)Buffer)->Header.BlockType = EFI_HII_SIBT_STRING_UCS2;
        Buffer += sizeof(EFI_HII_SIBT_STRING_UCS2_BLOCK);
        Size = StrSize16(Found->String);
        StrCpy16((CHAR16 *)Buffer, Found->String);
        Buffer += Size;
        CurrentStringId = Found->StringId;
    }
    ((EFI_HII_SIBT_END_BLOCK *)Buffer)->Header.BlockType = EFI_HII_SIBT_END;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   UpdateStringPackages
//
//  Description:
//  This function updates string package with strings contained in private storage 
//
//  Input:
// 	IN EFI_HII_HANDLE Handle - Handle of package list to update
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateStringPackages(EFI_HII_HANDLE Handle)
{
	DLIST		 *PackageList;
	PACKAGE_LINK *Link;
	PACKAGE_LINK *NewLink;
    EFI_HII_STRING_PACKAGE_HDR *StringPackage;
    UINT8 *Buffer;
    UINTN Size;

	PackageList = &(((PACKAGE_LIST_RECORD *)Handle)->PackageList);
	Link = (PACKAGE_LINK *)(PackageList->pHead);    

	while(Link != NULL)
	{
        if(Link->Package.Type == EFI_HII_PACKAGE_STRINGS)
        {
            StringPackage = (EFI_HII_STRING_PACKAGE_HDR *) &(Link->Package);
            Size = GetStringBlockSize((PACKAGE_LIST_RECORD *)Handle, StringPackage->Language);

            if(Size != 0)
            {
                Size += StringPackage->HdrSize;
                NewLink = (PACKAGE_LINK *) CreateNewLink((UINT32)Size);
                if(NewLink == NULL)
                    return EFI_OUT_OF_RESOURCES;

                MemCpy((VOID *) &(NewLink->Package), 
                       (VOID *) &(Link->Package), 
                       StringPackage->HdrSize);
                NewLink->Package.Length = (UINT32)Size;
                Buffer = (UINT8 *) &(NewLink->Package);
                Buffer += StringPackage->HdrSize;
    
                GetStringBlock((PACKAGE_LIST_RECORD *)Handle, StringPackage->Language, Buffer);

                DListInsert(PackageList, (DLINK *)NewLink, (DLINK *)Link);
                DListDelete(PackageList, (DLINK *)Link);
                pBS->FreePool(Link);
                Link = NewLink;
            }
        }
        Link = (PACKAGE_LINK *)Link->Link.pNext;
    }            
    return EFI_SUCCESS;
}
    
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   StrSize8
//
//  Description:
//  This function returns ASCII string size in bytes 
//
//  Input:
// 	IN CHAR8 *String - Pointer to string
//
//  Output:
//  UINT32 - Size of string in bytes including nul-terminator
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 StrSize8(CHAR8 *String)
{
	UINT32 Size = 1;
	while(*String++)
		Size++;
	return Size;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   StrSize16
//
//  Description:
//  This function returns UNICODE string size in bytes 
//
//  Input:
// 	IN CHAR16 *String - Pointer to string
//
//  Output:
//  UINT32 - Size of string in bytes including nul-terminator
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 StrSize16(CHAR16 *String)
{
	UINT32 Size = 2;
	while(*String++)
		Size += 2;
	return Size;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   StrCpy8
//
//  Description:
//  This function copies one ASCII string into another 
//
//  Input:
// 	IN CHAR8 *Dest - Pointer to destination string
// 	IN CHAR8 *Src - Pointer to source string
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StrCpy8(CHAR8 *Dest, CHAR8 *Src)
{
	MemCpy(Dest, Src, StrSize8(Src));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   StrCpy16
//
//  Description:
//  This function copies one UNICODE string into another 
//
//  Input:
// 	IN CHAR16 *Dest - Pointer to destination string
// 	IN CHAR16 *Src - Pointer to source string
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StrCpy16(CHAR16 *Dest, CHAR16 *Src)
{
	MemCpy(Dest, Src, StrSize16(Src));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   StrCmp8
//
//  Description:
//  This function compares two ASCII strings 
//
//  Input:
// 	IN CHAR8 *Dest - Pointer to destination string
// 	IN CHAR8 *Src - Pointer to source string
//
//  Output:
//  INTN - Zero if strings are equal, non-zero otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN StrCmp8(CHAR8 *Dest, CHAR8 *Src)
{
	return MemCmp(Dest, Src, StrSize8(Src));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   StrCmp16
//
//  Description:
//  This function compares two UNICODE strings 
//
//  Input:
// 	IN CHAR16 *Dest - Pointer to destination string
// 	IN CHAR16 *Src - Pointer to source string
//
//  Output:
//  INTN - Zero if strings are equal, non-zero otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN StrCmp16(CHAR16 *Dest, CHAR16 *Src)
{
	return MemCmp(Dest, Src, StrSize16(Src));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetAvailableFontId
//
//  Description:
//  This function returns available font ID number
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - pointer to package list were font belongs
//
//  Output:
//  UINT16 - font ID number
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetAvailableFontId(
    IN PACKAGE_LIST_RECORD *PackageList
)
{
    UINT16 Id = 0;
    STRING_FONT_LINK *Link = (STRING_FONT_LINK *)PackageList->StringFontList.pHead;
    while(Link != NULL) {
        Id = (Link->FontId > Id) ? Link->FontId : Id;
        Link = (STRING_FONT_LINK *)Link->Link.pNext;
    }
    return Id + 1;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindStringFontInfoByTemplate
//
//  Description:
//  This function searches available fonts and returns font ID if match found
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - pointer to package list were font belongs
//  IN EFI_FONT_INFO *Template - pointer to font description
//  OUT UINT16 *FontId - pointer where to return font ID
//
//  Output:
//  EFI_SUCCESS - font found
//  EFI_NOT_FOUND - font not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindStringFontInfoByTemplate(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN EFI_FONT_INFO *Template,
    OUT UINT16 *FontId
)
{
    STRING_FONT_LINK *Link = (STRING_FONT_LINK *)PackageList->StringFontList.pHead;
    EFI_FONT_INFO *Info;

    while(Link != NULL) {
        Info = (EFI_FONT_INFO *)(Link + 1);
        if(!MemCmp(Info, Template, Link->FontInfoSize)) {
            *FontId = Link->FontId;
            return EFI_SUCCESS;
        }
        Link = (STRING_FONT_LINK *)Link->Link.pNext;
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindStingFontInfoById
//
//  Description:
//  This function searches available fonts and returns font description if match found
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - pointer to package list were font belongs
//  IN UINT16 FontId - font ID to find
//  OUT EFI_FONT_INFO **Info - pointer where to store pointer to font description
//
//  Output:
//  EFI_SUCCESS - font found
//  EFI_NOT_FOUND - font not found
//  EFI_OUT_OF_RESOURCES - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindStingFontInfoById(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN UINT16 FontId,
    OUT EFI_FONT_INFO **Info
)
{
    static CHAR16 DefaultFontName[] = L"System font";
    STRING_FONT_LINK *Link = (STRING_FONT_LINK *)PackageList->StringFontList.pHead;
    UINTN StrSize;
    EFI_STATUS Status;

    while(Link != NULL) {
        if(Link->FontId == FontId) {
            Status = pBS->AllocatePool(EfiBootServicesData, Link->FontInfoSize, Info);
            if(EFI_ERROR(Status))
                return Status;

            MemCpy(*Info, (VOID *)(Link + 1), Link->FontInfoSize);
            return EFI_SUCCESS;
        }
        Link = (STRING_FONT_LINK *)Link->Link.pNext;
    }
//font not found, return default font
    StrSize = Wcslen(DefaultFontName) * sizeof(CHAR16);
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(EFI_FONT_INFO) + StrSize, Info);
    if(!EFI_ERROR(Status)) {
        (*Info)->FontSize = EFI_GLYPH_HEIGHT;
        (*Info)->FontStyle = EFI_HII_FONT_STYLE_NORMAL;
        Wcscpy((*Info)->FontName, DefaultFontName);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddStringFont
//
//  Description:
//  This function adds font to font database and assigns font ID if latter was 
//  not supplied
//
//  Input:
// 	IN PACKAGE_LIST_RECORD *PackageList - pointer to package list were font belongs
//  IN UINT16 FontId - font ID
//  IN UINT16 FontSize - font size
//  IN EFI_HII_FONT_STYLE FontStyle - font style
//  IN CHAR16 *FontName - pointer to font name
//  OUT UINT16 *NewFontId OPTIONAL - pointer where to store assigned font ID
//
//  Output:
//  EFI_SUCCESS - font found
//  EFI_NOT_FOUND - font not found
//  EFI_OUT_OF_RESOURCES - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddStringFont(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN UINT16 FontId,
    IN UINT16 FontSize,
    IN EFI_HII_FONT_STYLE FontStyle,
    IN CHAR16 *FontName,
    OUT UINT16 *NewFontId OPTIONAL
)
{
    UINT16 Fid;
    UINT32 FontNameSize;
    STRING_FONT_LINK *AddLink;
    EFI_FONT_INFO *FontInfo;

    Fid = (FontId == INVALID_FONT_ID) ? GetAvailableFontId(PackageList) : FontId;

    FontNameSize = (UINT32)((Wcslen(FontName)) * sizeof(CHAR16)); //null-terminator already accounted for in EFI_FONT_INFO structure
    AddLink = CreateNewLink((UINT32)(sizeof(STRING_FONT_LINK) + sizeof(EFI_FONT_INFO)) + FontNameSize);
    if(AddLink == NULL)
        return EFI_OUT_OF_RESOURCES;

    AddLink->FontId = Fid;
    AddLink->FontInfoSize = (UINT32)sizeof(EFI_FONT_INFO) + FontNameSize;
    FontInfo = (EFI_FONT_INFO *)(AddLink + 1);
    FontInfo->FontSize = FontSize;
    FontInfo->FontStyle = FontStyle;
    Wcscpy(FontInfo->FontName, FontName);
    DListAdd(&(PackageList->StringFontList), (DLINK *)AddLink);
    if(NewFontId)
        *NewFontId = Fid;
    return EFI_SUCCESS;
}

#pragma warning (default : 4090)

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
