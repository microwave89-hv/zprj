//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/FrameworkHii/FrameworkHiiUtils.c 3     2/23/10 10:17p Felixp $
//
// $Revision: 3 $
//
// $Date: 2/23/10 10:17p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/FrameworkHii/FrameworkHiiUtils.c $
// 
// 3     2/23/10 10:17p Felixp
// SetBrowserData function is added
// 
// 2     11/24/09 10:40a Felixp
// 
// 1     10/09/09 6:10p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	UefiHiiUtils.c
//
// Description:	Framework HII 0.91 HII Utilities Protocol Implementation
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Protocol/HiiUtilities.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DevicePath.h>

static EFI_HII_PROTOCOL *Hii=NULL;
static EFI_GUID HiiResourcesFfsSectionGuid= HII_RESOURCES_FFS_SECTION_GUID;

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
	for(i=0; i<NumberOfCallbacks; i++)
	{
		if (
			   FormSet->Class==CallbackInfo[i].Class
			&& FormSet->SubClass==CallbackInfo[i].SubClass
			&& (!CallbackInfo[i].pGuid || !guidcmp(&FormSet->Guid,CallbackInfo[i].pGuid))
		)
		{
			if (CallbackInfo[i].pFormCallback)
			{
				EFI_HANDLE Handle=NULL;
				Status=pBS->InstallProtocolInterface(&Handle, &gEfiFormCallbackProtocolGuid, EFI_NATIVE_INTERFACE, CallbackInfo[i].pFormCallback);
				if (EFI_ERROR(Status)) return Status;
				FormSet->CallbackHandle=(EFI_PHYSICAL_ADDRESS)Handle;
                if (CallbackHandle) *CallbackHandle=Handle;
			}
			if (CallBackFound) *CallBackFound=&CallbackInfo[i];
			return EFI_SUCCESS;
		}
	}
	if (CallBackFound) *CallBackFound=NULL;
	return EFI_NOT_FOUND;
}

static EFI_STATUS PublishPackages(
    IN VOID *PackagePointers, IN UINTN NumberOfPackages, 
    IN EFI_GUID *PackageGuid, IN EFI_HANDLE DriverHandle OPTIONAL,
    OUT EFI_HII_HANDLE *HiiHandle
){
    EFI_STATUS Status;
	EFI_HII_PACKAGES *PackageList;
    EFI_HII_PACK_HEADER **Packages = PackagePointers;
    
    if (   !Hii 
        && EFI_ERROR(Status=pBS->LocateProtocol(
                        &gEfiHiiProtocolGuid, NULL, &Hii
           ))
    ) return Status;

	PackageList = Malloc(
        sizeof(EFI_HII_PACKAGES)+sizeof(EFI_HII_PACK_HEADER*)*NumberOfPackages
    );
    if(PackageList==NULL) return EFI_OUT_OF_RESOURCES;
    PackageList->NumberOfPackages=NumberOfPackages;
	PackageList->GuidId = PackageGuid;
	pBS->CopyMem(
        PackageList+1, Packages, sizeof(EFI_HII_PACK_HEADER*)*NumberOfPackages
    );
	Status = Hii->NewPack(Hii, PackageList, HiiHandle);
    pBS->FreePool(PackageList);
    return Status;
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
	EFI_HII_PACK_HEADER *pPack;

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
    pPack = (EFI_HII_PACK_HEADER*)(pSection+1);
    if (pPack->Type == EFI_HII_STRING){
        Status = PublishPackages(
            &pPack, 1, 
            &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(Image->FilePath))->NameGuid,
            NULL, HiiHandle
        );
    }else{
		Status = EFI_INVALID_PARAMETER;
	}
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
    EFI_HII_PACK_HEADER **IfrPackagPtr, **GlobalPackagPtr, **SharedPackagPtr;
    UINTN NumberOfIfrPackages, NumberOfGlobalPackages, NumberOfSharedPackages, i;
    UINT8 *PackagePtrBuffer;
    EFI_HII_PACK_HEADER *PackagePtr;

    PackagePtrBuffer = Malloc(3*pSection->NumberOfPackages*sizeof(EFI_HII_PACK_HEADER*));
    IfrPackagPtr = (EFI_HII_PACK_HEADER**)PackagePtrBuffer;
    GlobalPackagPtr = IfrPackagPtr+pSection->NumberOfPackages;
    SharedPackagPtr = GlobalPackagPtr+pSection->NumberOfPackages;
    NumberOfIfrPackages = 0;
    NumberOfGlobalPackages = 0;
    NumberOfSharedPackages = 0;

    PackagePtr = (EFI_HII_PACK_HEADER*)(pSection+1);
	while(PackagePtr < (EFI_HII_PACK_HEADER*)((UINT8*)pSection+SectionSize)){
		switch(PackagePtr->Type){
        case EFI_HII_IFR:
            IfrPackagPtr[NumberOfIfrPackages++]=PackagePtr;
            break;
        case EFI_HII_FONT: case EFI_HII_KEYBOARD:
            GlobalPackagPtr[NumberOfGlobalPackages++]=PackagePtr;
            break;
        default:
            SharedPackagPtr[NumberOfSharedPackages++]=PackagePtr;
            if (PackagePtr->Type==EFI_HII_STRING){
			    while(PackagePtr->Length)
				    PackagePtr = (EFI_HII_PACK_HEADER*)((UINT8*)PackagePtr+PackagePtr->Length);
                PackagePtr = (EFI_HII_PACK_HEADER*)((UINT8*)PackagePtr+sizeof(EFI_HII_STRING_PACK));
                continue;
            }
            break;
        }
        PackagePtr = (EFI_HII_PACK_HEADER*)((UINT8*)PackagePtr+PackagePtr->Length);
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
    if (   !Hii 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiProtocolGuid, NULL, &Hii))
    ) return EFI_NOT_FOUND;
    return Hii->GetString(
        Hii, HiiHandle, StringId, TRUE, NULL, StringSize, String
    );
}

//TODO header
static EFI_STATUS SetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN EFI_STRING String
){
    if (   !Hii 
        && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiProtocolGuid, NULL, &Hii))
    ) return EFI_NOT_FOUND;
    return Hii->NewString(
        Hii, L"   ", HiiHandle, &StringId, String
    );
}

static EFI_STATUS GetBrowserData(
    IN UINTN *BufferSize, OUT VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
){
    return EFI_UNSUPPORTED;
}

static EFI_STATUS SetBrowserData(
    IN UINTN BufferSize, IN VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
){
    return EFI_UNSUPPORTED;
}

HII_UTILITIES_PROTOCOL HiiUtilitiesProtocol = {
    LoadResources, LoadStrings, PublishPackages, 
    GetBrowserData, SetBrowserData, GetString, SetString
};

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************