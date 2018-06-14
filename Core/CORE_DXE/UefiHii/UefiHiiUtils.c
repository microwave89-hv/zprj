//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/UefiHiiUtils.c 16    5/22/12 4:38p Artems $
//
// $Revision: 16 $
//
// $Date: 5/22/12 4:38p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/UefiHiiUtils.c $
// 
// 16    5/22/12 4:38p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	In certain cases system font is absent
// [RootCause]  	When font FFS file is not found system doesn't publish
// system font
// [Solution]  	If font FFS file is not found, publish font supplied with
// Core
// [Files]  		UefiHiiUtils.c
// 
// 15    4/30/12 3:52p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Modified GraphicsConsole driver to output whole string
// instead of symbol-by-symbol output
// [Files]  		Gc.c, AmiDxeLib.h, EfiLib.c, UefiHiiUtils.c
// 
// 14    1/05/12 5:05p Artems
// EIP 76735: Font FFS file is not loaded in framework mode, when in
// nested FV
// 
// 13    1/05/11 12:12p Artems
// EIP 51298: BufferSize value gets corrupted after call to ConfigToBlock
// function - fixed
// 
// 12    10/07/10 12:18p Felixp
// Minor bug fix in LoadSystemFont: don't call FreePool if font section
// has not been read.
// 
// 11    10/01/10 4:44p Artems
// Added implementation of function SetBrowserData
// 
// 10    3/22/10 3:25p Felixp
// SetCallback bug fix (the bug introduced during previous check in).
// 
// 9     3/12/10 2:21p Felixp
// Enhencement: LoadResources is updated to properly publish the packages
// when NumberOfCallbacks is zero.
// 
// 7     2/23/10 10:30p Felixp
// SetBrowserData function is added.
// 
// 6     2/19/10 4:15p Felixp
// GetString function is  updated: if the string is not defined for the
// PlatformLang , try with the default language.
//   If still no luck, try English.
// 
// 5     2/12/10 5:47p Felixp
// Bug fix in LoadResources and LoadString functions
// (memory corruption in projects with more than one supported language).
// 
// 4     11/25/09 11:27a Felixp
// Action parameter of the Callback function is updated  based on UEFI
// errata
// 
// 3     11/24/09 4:39p Felixp
// 
// 2     11/24/09 11:27a Felixp
// GetString udpated: if PlatformLang variable does not exist use default
// language instead of English.
// 
// 1     10/09/09 6:12p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	UefiHiiUtils.c
//
// Description:	UEFI 2.1 HII Utilities Protocol Implementation
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Protocol/HiiUtilities.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/HiiConfigRouting.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DevicePath.h>
#include "HiiPrivate.h"

EFI_STATUS HiiAccessExtractConfig(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Request,
    OUT EFI_STRING *Progress,
    OUT EFI_STRING *Results
);
EFI_STATUS HiiAccessRouteConfig(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Configuration,
    OUT EFI_STRING *Progress
);
EFI_STATUS HiiAccessFormCallback(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID QuestionId,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
);

VOID StripValuePattern(
    IN OUT EFI_STRING String,
    IN UINTN          Size
);

UINT32 StrSize16(
    IN CHAR16 *String
);

static EFI_HII_DATABASE_PROTOCOL *HiiDatabase=NULL;
static EFI_HII_STRING_PROTOCOL *HiiString=NULL;
static EFI_FORM_BROWSER2_PROTOCOL  *FormBrowser = NULL;
static EFI_HII_CONFIG_ROUTING_PROTOCOL *HiiConfigRouting = NULL;

static EFI_GUID HiiResourcesFfsSectionGuid= HII_RESOURCES_FFS_SECTION_GUID;
static EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
static CHAR8 *PlatformLang = NULL;

extern const char *DefaultLanguageCode;
extern SIMPLE_FONT DefaultFont[];

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: SetCallback
//
// Description:
//  EFI_STATUS SetCallback(EFI_HII_IFR_PACK *pIfr,
// UINTN NumberOfCallbacks, CALLBACK_INFO *CallbackInfo,
// CALLBACK_INFO **CallBackFound)
//
// Input:
//
// Output:
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
static EFI_STATUS SetCallback(
    EFI_LOADED_IMAGE_PROTOCOL *Image,
	EFI_IFR_FORM_SET *FormSet, UINTN NumberOfCallbacks,
	CALLBACK_INFO *CallbackInfo, CALLBACK_INFO **CallBackFound,
    EFI_HANDLE *CallbackHandle 
)
{
	UINTN i;
	EFI_STATUS Status;
    EFI_HANDLE Handle=NULL;
    EFI_DEVICE_PATH_PROTOCOL *pPath, *pPath2;
    CALLBACK_INFO *CallbackInfoPtr;

    static EFI_HII_CONFIG_ACCESS_PROTOCOL DefaultConfigAccess = {
        HiiAccessExtractConfig, HiiAccessRouteConfig, HiiAccessFormCallback
    };
    static CALLBACK_INFO DefaultCallbackInfo = {
	    NULL,&DefaultConfigAccess, 0, 0, NULL
    };
    static VENDOR_DEVICE_PATH FormSetDevicePathNode = {
        {
            MEDIA_DEVICE_PATH, MEDIA_VENDOR_DP,
            sizeof(VENDOR_DEVICE_PATH)
        },
        {0}
    };

	for(  i=0
        ;    i<NumberOfCallbacks
          && (      CallbackInfo[i].pGuid == NULL
                ||  guidcmp(&FormSet->Guid,CallbackInfo[i].pGuid) != 0
             )
        ; i++
    );
    if (i==NumberOfCallbacks){
        CallbackInfoPtr = &DefaultCallbackInfo;
    }else{
        CallbackInfoPtr = &CallbackInfo[i];
        if (CallbackInfoPtr->pFormCallback == NULL){
            CallbackInfoPtr->pFormCallback = &DefaultConfigAccess;  
        }else{
            if (CallbackInfoPtr->pFormCallback->ExtractConfig==NULL)
                CallbackInfoPtr->pFormCallback->ExtractConfig = 
                    HiiAccessExtractConfig;
            if (CallbackInfoPtr->pFormCallback->RouteConfig==NULL)
                CallbackInfoPtr->pFormCallback->RouteConfig = 
                    HiiAccessRouteConfig;
            if (CallbackInfoPtr->pFormCallback->Callback==NULL)
                CallbackInfoPtr->pFormCallback->Callback = 
                    HiiAccessFormCallback;
        }
    }
            Status=pBS->HandleProtocol(Image->DeviceHandle, &guidDevicePath, &pPath);
            if (EFI_ERROR(Status)) pPath=NULL;
            pPath = DPAddNode(pPath, Image->FilePath);
            FormSetDevicePathNode.Guid = FormSet->Guid;
            pPath2 = DPAddNode(pPath, &FormSetDevicePathNode.Header);
            pBS->FreePool(pPath);
            Status = pBS->InstallMultipleProtocolInterfaces(
                &Handle, 
                &guidDevicePath, pPath2,
        &gEfiHiiConfigAccessProtocolGuid, CallbackInfoPtr->pFormCallback,
                NULL
            );
			if (EFI_ERROR(Status)) return Status;
    if (CallbackHandle) *CallbackHandle=Handle;
    if (CallBackFound){
        *CallBackFound=  (CallbackInfoPtr == &DefaultCallbackInfo) 
                       ? NULL 
                       : CallbackInfoPtr;
    }
	return EFI_SUCCESS;
}

static EFI_STATUS PublishPackages(
    IN VOID *PackagePointers, IN UINTN NumberOfPackages, 
    IN EFI_GUID *PackageGuid, IN EFI_HANDLE DriverHandle OPTIONAL,
    OUT EFI_HII_HANDLE *HiiHandle
){
	EFI_STATUS Status;
    EFI_HII_PACKAGE_LIST_HEADER *PackageList;
    UINTN i;
    UINT32 PackageLength; 
    UINT8 *PackagePtr;
    EFI_HII_PACKAGE_HEADER **Packages = PackagePointers;
    if (NumberOfPackages==0) return EFI_SUCCESS;
    if (   !HiiDatabase 
        && EFI_ERROR(Status=pBS->LocateProtocol(
                        &gEfiHiiDatabaseProtocolGuid, NULL, &HiiDatabase
           ))
    ) return Status;
    //calculate the package list length
    PackageLength =   sizeof(EFI_HII_PACKAGE_LIST_HEADER) 
                    + sizeof(EFI_HII_PACKAGE_HEADER); //package list terminator
    for(i=0; i<NumberOfPackages; i++){
        PackageLength += Packages[i]->Length;
    }
    PackageList = Malloc(PackageLength);
    if(PackageList==NULL) return EFI_OUT_OF_RESOURCES;
    PackageList->PackageListGuid = *PackageGuid;
    PackageList->PackageLength = PackageLength;

    PackagePtr = (UINT8*)(PackageList+1);
    for(  i=0; i<NumberOfPackages; i++){
        pBS->CopyMem(PackagePtr, Packages[i], Packages[i]->Length);
        PackagePtr += Packages[i]->Length;
    }
    ((EFI_HII_PACKAGE_HEADER *)PackagePtr)->Length = sizeof(EFI_HII_PACKAGE_HEADER);
    ((EFI_HII_PACKAGE_HEADER *)PackagePtr)->Type = EFI_HII_PACKAGE_END;

    Status = HiiDatabase->NewPackageList(
        HiiDatabase, PackageList, DriverHandle, HiiHandle
    );
    pBS->FreePool(PackageList);
    return Status;
}

UINT32 GetNumerOfResourcePackages(
    HII_RESOURCE_SECTION_HEADER *pSection, UINTN SectionSize
){
    EFI_HII_PACKAGE_HEADER *PackagePtr;
    UINT32 NumberOfPackages = 0;
    PackagePtr = (EFI_HII_PACKAGE_HEADER*)(pSection+1);
	while(PackagePtr < (EFI_HII_PACKAGE_HEADER*)((UINT8*)pSection+SectionSize)){
        PackagePtr = (EFI_HII_PACKAGE_HEADER*)((UINT8*)PackagePtr+PackagePtr->Length);
        NumberOfPackages++;
    }
    return NumberOfPackages;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: LoadStrings
//
// Description:
//  EFI_STATUS LoadStrings(EFI_HANDLE ImageHandle,
// EFI_HII_HANDLE *HiiHandle)
//
// Input:
//
// Output:
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
static EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, EFI_HII_HANDLE *HiiHandle
)
{
	EFI_STATUS Status;
	EFI_LOADED_IMAGE_PROTOCOL *Image;
	HII_RESOURCE_SECTION_HEADER *pSection;
	UINTN SectionSize;
    EFI_HII_PACKAGE_HEADER *pPack;
    EFI_HII_PACKAGE_HEADER **StringPackagPtr;
    UINTN NumberOfStringPackages;
	if (EFI_ERROR(Status=pBS->HandleProtocol(
                        ImageHandle, &gEfiLoadedImageProtocolGuid, &Image
        ))
    ) return Status;
#if defined(EMBEDDED_RESOURCES) && EMBEDDED_RESOURCES==1
{
#define AMIRC_PESECTION_NAME 0x5f534552494d415f//_AMIRES_
	UINT8 *pData;
	pData = FindPeSection(Image->ImageBase, AMIRC_PESECTION_NAME, &SectionSize);
	if (!pData) return EFI_NOT_FOUND;
	pSection = Malloc(SectionSize);
	pBS->CopyMem(pSection,pData,SectionSize);
    Status = EFI_SUCCESS;
}
#else
{
	Status=ReadImageResource(ImageHandle,&HiiResourcesFfsSectionGuid,&pSection,&SectionSize);
	if (EFI_ERROR(Status)) return Status;
}
#endif
    //Calculate number of packages. 
    //Original value of pSection->NumberOfPackages treats string packages 
    //for multiple languages as a single package. We need the real number of packages.
    pSection->NumberOfPackages = GetNumerOfResourcePackages(pSection,SectionSize);

    pPack = (EFI_HII_PACKAGE_HEADER *)(pSection + 1);

    StringPackagPtr = Malloc(pSection->NumberOfPackages*sizeof(EFI_HII_PACKAGE_HEADER*));
    NumberOfStringPackages=0;
    while(pPack < (EFI_HII_PACKAGE_HEADER*)((UINT8*)pSection+SectionSize)){
        if (pPack->Type != EFI_HII_PACKAGE_STRINGS){
            Status=EFI_INVALID_PARAMETER;
            break;
        }
        StringPackagPtr[NumberOfStringPackages++]=pPack;
        pPack = (EFI_HII_PACKAGE_HEADER*)((UINT8*)pPack+pPack->Length);
    }
    Status = PublishPackages(
        StringPackagPtr, NumberOfStringPackages,
        &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(Image->FilePath))->NameGuid,
        NULL, HiiHandle
    );
    pBS->FreePool(StringPackagPtr);
	pBS->FreePool(pSection);
	return Status;	
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: LoadResources
//
// Description:
//  EFI_STATUS LoadResources(EFI_HANDLE ImageHandle,
// UINTN NumberOfCallbacks, CALLBACK_INFO *CallbackInfo,
// INIT_HII_PACK InitFunction)
//
// Input:
//
// Output:
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
static EFI_STATUS LoadResources(
	EFI_HANDLE ImageHandle, UINTN NumberOfCallbacks,
	CALLBACK_INFO *CallbackInfo, INIT_HII_PACK InitFunction
)
{
	EFI_STATUS Status;
	EFI_HII_HANDLE HiiHandle;
	EFI_LOADED_IMAGE_PROTOCOL *Image;
	HII_RESOURCE_SECTION_HEADER *pSection;
	UINTN SectionSize;
	CALLBACK_INFO *pCallBackFound;
	if (EFI_ERROR(Status=pBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, &Image))) return Status;
#if defined(EMBEDDED_RESOURCES) && EMBEDDED_RESOURCES==1
{
#define AMIRC_PESECTION_NAME 0x5f534552494d415f//_AMIRES_
	UINT8 *pData;
	pData = FindPeSection(Image->ImageBase, AMIRC_PESECTION_NAME, &SectionSize);
	if (!pData) return EFI_NOT_FOUND;
	pSection = Malloc(SectionSize);
	pBS->CopyMem(pSection,pData,SectionSize);
}
#else
{
	Status=ReadImageResource(ImageHandle,&HiiResourcesFfsSectionGuid,&pSection,&SectionSize);
	if (EFI_ERROR(Status)) return Status;
}
#endif
{
    EFI_HII_PACKAGE_HEADER **IfrPackagPtr, **GlobalPackagPtr, **SharedPackagPtr;
    UINTN NumberOfIfrPackages, NumberOfGlobalPackages, NumberOfSharedPackages, i;
    UINT8 *PackagePtrBuffer;
    EFI_HII_PACKAGE_HEADER *PackagePtr;

    //Calculate number of packages. 
    //Original value of pSection->NumberOfPackages treats string packages 
    //for multiple languages as a single package. We need the real number of packages.
    pSection->NumberOfPackages = GetNumerOfResourcePackages(pSection,SectionSize);

    PackagePtrBuffer = Malloc(3*pSection->NumberOfPackages*sizeof(EFI_HII_PACKAGE_HEADER*));
    IfrPackagPtr = (EFI_HII_PACKAGE_HEADER**)PackagePtrBuffer;
    GlobalPackagPtr = IfrPackagPtr+pSection->NumberOfPackages;
    SharedPackagPtr = GlobalPackagPtr+pSection->NumberOfPackages;
    NumberOfIfrPackages = 0;
    NumberOfGlobalPackages = 0;
    NumberOfSharedPackages = 0;

    PackagePtr = (EFI_HII_PACKAGE_HEADER*)(pSection+1);
	while(PackagePtr < (EFI_HII_PACKAGE_HEADER*)((UINT8*)pSection+SectionSize)){
		switch(PackagePtr->Type){
        case EFI_HII_PACKAGE_FORMS:
            IfrPackagPtr[NumberOfIfrPackages++]=PackagePtr;
            break;
        case EFI_HII_PACKAGE_FONTS: case EFI_HII_PACKAGE_KEYBOARD_LAYOUT:
            GlobalPackagPtr[NumberOfGlobalPackages++]=PackagePtr;
            break;
        default:
            SharedPackagPtr[NumberOfSharedPackages++]=PackagePtr;
            break;
        }
        PackagePtr = (EFI_HII_PACKAGE_HEADER*)((UINT8*)PackagePtr+PackagePtr->Length);
    }
    Status = PublishPackages(
        GlobalPackagPtr, NumberOfGlobalPackages,
        &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(Image->FilePath))->NameGuid,
        NULL, &HiiHandle
    );
    for(i=0; i<NumberOfIfrPackages; i++){
        EFI_HANDLE CallbackHandle;

        SharedPackagPtr[NumberOfSharedPackages]=IfrPackagPtr[i];
        SetCallback(
            Image, (EFI_IFR_FORM_SET*)(IfrPackagPtr[i]+1),
            NumberOfCallbacks,CallbackInfo,&pCallBackFound,&CallbackHandle
        );
        Status = PublishPackages(
            SharedPackagPtr, NumberOfSharedPackages+1, 
            &((EFI_IFR_FORM_SET*)(IfrPackagPtr[i]+1))->Guid,
            CallbackHandle, &HiiHandle
        );
		if (pCallBackFound) pCallBackFound->HiiHandle=HiiHandle;
		if (InitFunction) InitFunction(HiiHandle,pCallBackFound);
		pCallBackFound=NULL;
    }
    pBS->FreePool(PackagePtrBuffer);
	pBS->FreePool(pSection);
}
	return EFI_SUCCESS;	
}

//TODO: header
static EFI_STATUS GetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, OUT EFI_STRING String
){
    EFI_STATUS Status;

    if (   !HiiString 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &HiiString))
    ) return EFI_NOT_FOUND;
    if (PlatformLang==NULL){
        UINTN Size;
        if (EFI_ERROR(GetEfiVariable(
                L"PlatformLang", &EfiVariableGuid, NULL, &Size, &PlatformLang
        ))) PlatformLang = (CHAR8*)DefaultLanguageCode;
    }
    Status = HiiString->GetString(
        HiiString, PlatformLang, HiiHandle,StringId, String, StringSize, NULL
    );
    // If the string representation for the PlatformLang is not defined,
    // try with the default language.
    // If still no luck, try English
    if (Status==EFI_INVALID_LANGUAGE){
        Status = HiiString->GetString(
            HiiString, (CHAR8*)DefaultLanguageCode, HiiHandle,
            StringId, String, StringSize, NULL
        );
        if (Status==EFI_INVALID_LANGUAGE)
            Status = HiiString->GetString(
                HiiString, LANGUAGE_CODE_ENGLISH, HiiHandle,
                StringId, String, StringSize, NULL
            );
    }
    return Status;
}

//TODO header
static EFI_STATUS SetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN EFI_STRING String
){
	CHAR8 *LanguageList = NULL;
	UINTN Size = 0;
    EFI_STATUS Status;

    if (   !HiiString 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &HiiString))
    ) return EFI_NOT_FOUND;

    Status = HiiString->GetLanguages(HiiString, HiiHandle, LanguageList, &Size);
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;
    LanguageList = Malloc(Size);
    Status = HiiString->GetLanguages(HiiString, HiiHandle, LanguageList, &Size);
    if (!EFI_ERROR(Status)){
        CHAR8 *CurrentLang, *EndOfCurrentLang;
        EndOfCurrentLang = LanguageList;
        while(EndOfCurrentLang < LanguageList+Size){
            CHAR8 OriginalChar;
            CurrentLang = EndOfCurrentLang;
            while(*EndOfCurrentLang!=';'&&*EndOfCurrentLang!=0) EndOfCurrentLang++;
            OriginalChar = *EndOfCurrentLang;
            *EndOfCurrentLang = 0;
            Status = HiiString->SetString(
                HiiString, HiiHandle, StringId, CurrentLang, String, NULL
            );
            if (EFI_ERROR(Status)) break;
            *EndOfCurrentLang = OriginalChar;
            EndOfCurrentLang++;
        }
    }
    pBS->FreePool(LanguageList);
    return Status;
}

static EFI_STATUS GetBrowserData(
    IN UINTN *BufferSize, OUT VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
){
    UINTN StringDataSize = 0;
    CHAR16 *StringData = NULL;
    EFI_STATUS Status;
    EFI_STRING Progress;

    if (   !FormBrowser 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiFormBrowser2ProtocolGuid, NULL, &FormBrowser))
    ) return EFI_NOT_FOUND;
    if (   !HiiConfigRouting 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiConfigRoutingProtocolGuid, NULL, &HiiConfigRouting))
    ) return EFI_NOT_FOUND;

    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;
    StringData = Malloc(StringDataSize);
    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (!EFI_ERROR(Status)){
        StringDataSize = *BufferSize;       //preserve passed buffer size value, as 
                                            //ConfigToBlock may change it as per UEFI 2.1 spec
                                            //it will contain index of last updated byte
        Status = HiiConfigRouting->ConfigToBlock(
            HiiConfigRouting, StringData, Buffer, BufferSize, &Progress
        );
        *BufferSize = StringDataSize;       //restore original value
    }
    pBS->FreePool(StringData);
    return Status;
}

static EFI_STATUS SetBrowserData(
    IN UINTN BufferSize, IN VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL //TODO: Can it be optional??? 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
)
{
    UINTN StringDataSize = 0;
    CHAR16 *StringData = NULL;
    EFI_STATUS Status;
    EFI_STRING Config;
    EFI_STRING Progress;

    if (   !FormBrowser 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiFormBrowser2ProtocolGuid, NULL, &FormBrowser))
    ) return EFI_NOT_FOUND;
    if (   !HiiConfigRouting 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiConfigRoutingProtocolGuid, NULL, &HiiConfigRouting))
    ) return EFI_NOT_FOUND;

    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;
    StringData = Malloc(StringDataSize);
    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (EFI_ERROR(Status))
        return Status;

//we have StringData in format &OFFSET=XXXX&WIDTH=XXXX&VALUE=XXXX&OFFSET=...
//in order for function BlockToConfig to work we need to modify StringData as follows:
//&OFFSET=XXXX&WIDTH=XXXX&OFFSET=... (i.e. remove all &VALUE=XXX patterns)

    StripValuePattern(StringData, StringDataSize);

    Status = HiiConfigRouting->BlockToConfig(
        HiiConfigRouting, StringData, Buffer, BufferSize,
        &Config, &Progress
    );

    if(!EFI_ERROR(Status)) {
        StringDataSize = StrSize16(Config);
        Status = FormBrowser->BrowserCallback(
            FormBrowser, &StringDataSize, Config, FALSE, 
            VarStoreGuid, VarStoreName
        );
        pBS->FreePool(Config);
    }

    pBS->FreePool(StringData);
    return Status;
}

EFI_STATUS LoadSystemFont(){
///// Load Font Pack
#define FONT_FFS_FILE_GUID { 0xdac2b117, 0xb5fb, 0x4964, { 0xa3, 0x12, 0xd, 0xcc, 0x77, 0x6, 0x1b, 0x9b } }
static EFI_GUID FontFfsFileGuid = FONT_FFS_FILE_GUID;
extern UINT8 UsStdNarrowGlyphData[];
	EFI_FIRMWARE_VOLUME_PROTOCOL *pFV;
	UINTN DataSize;
	EFI_GUID *pSectionGuid = NULL;
	UINT32 Authentication;
	EFI_HANDLE *pHandle;
	UINTN Number,i;
    EFI_STATUS FontStatus;
    EFI_HII_PACKAGE_HEADER *FontPackage;
    EFI_HII_HANDLE HiiFontHandle;

    FontPackage = (EFI_HII_PACKAGE_HEADER*)&UsStdNarrowGlyphData;
	FontStatus = pBS->LocateHandleBuffer(ByProtocol,&guidFV, NULL, &Number, &pHandle);
	for(i=0;i<Number; i++)
	{
		FontStatus=pBS->HandleProtocol(pHandle[i], &guidFV, &pFV);
		if (EFI_ERROR(FontStatus)) continue;
		pSectionGuid=NULL;
		DataSize=0;
		FontStatus=pFV->ReadSection (
			pFV,&FontFfsFileGuid,
			EFI_SECTION_FREEFORM_SUBTYPE_GUID,0, &pSectionGuid, &DataSize,
			&Authentication
	 	);
		if (!EFI_ERROR(FontStatus))
		{
			FontPackage=(EFI_HII_PACKAGE_HEADER*)((UINT32*)(pSectionGuid+1)+1);
			break;
		}
	}

    if (FontPackage->Type!=EFI_HII_PACKAGE_SIMPLE_FONTS){
        //The font package is in the Framework HII format
        //Convert the header to the UEFI HII format
        DataSize=FontPackage->Length;
        FontPackage = (EFI_HII_PACKAGE_HEADER*)((UINT8*)FontPackage+2);
        FontPackage->Type=EFI_HII_PACKAGE_SIMPLE_FONTS;
        FontPackage->Length=(UINT32)DataSize;
    }
	FontStatus = PublishPackages(&FontPackage, 1, &FontFfsFileGuid, NULL, &HiiFontHandle);
	if (pSectionGuid!=NULL) pBS->FreePool(pSectionGuid);
    return FontStatus;
}

static EFI_STATUS UtilGetGlyphWidth(
    IN CHAR16 Char,
    OUT UINT16 *Width
)
{
	EFI_STATUS Status = EFI_SUCCESS;

	if(DefaultFont[(UINTN)Char].NarrowGlyph != NULL) {
		*Width = ((DefaultFont[(UINTN)Char].NarrowGlyph)->Attributes & EFI_GLYPH_NON_SPACING) ? 0 : EFI_GLYPH_WIDTH;
	} else if(DefaultFont[(UINTN)Char].WideGlyph != NULL)	{
		*Width = ((DefaultFont[(UINTN)Char].WideGlyph)->Attributes & EFI_GLYPH_NON_SPACING) ? 0 : EFI_GLYPH_WIDE_WIDTH;
	} else if(DefaultFont[0xfffd].NarrowGlyph != NULL) {
        *Width = EFI_GLYPH_WIDTH;
		Status = EFI_WARN_UNKNOWN_GLYPH;
    } else if(DefaultFont[0xfffd].WideGlyph != NULL) {
        *Width = EFI_GLYPH_WIDE_WIDTH;
		Status = EFI_WARN_UNKNOWN_GLYPH;
    } else {
        *Width = 0;
		Status = EFI_WARN_UNKNOWN_GLYPH;
    }
	return Status;
}

HII_UTILITIES_PROTOCOL HiiUtilitiesProtocol = {
    LoadResources, LoadStrings, PublishPackages, 
    GetBrowserData, SetBrowserData, GetString, SetString, UtilGetGlyphWidth
};

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************