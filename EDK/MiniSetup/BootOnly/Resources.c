//**********************************************************************
//**********************************************************************
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/Resources.c 7     10/18/12 5:59a Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 5:59a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/Resources.c $
// 
// 7     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     5/02/11 3:31p Arunsb
// Changed for EDK library build. PI 1.1 support added.
// 
// 5     12/02/10 2:33p Madhans
// [TAG] - EIP 48169  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Code Cleanup and Compiler Warning need to resolved.
// [Rootcause] Warnings reported when we build AMI higher Warning level.
// [Solution]- 1. Fix the warnings and do the code cleanup. 
//             2. Introduce proper checks.
//             3. change the popupSel.c to not change the Option/variable
// cache to default or first option
//                when the variable cache is not matching with any of
// option.
// [Files] - commonoem.c bbs.c boot.c hiistring.c resource.c
// popuppassword.c popupsel.c
//           expression.c hii.c parse.c
// 
// 4     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 6     9/16/10 3:00p Madhans
// To Avoid build issues with TSE_USE_EDK_LIBRARY Building.
// 
// 5     7/12/10 4:49p Madhans
// EIP 39113: Sign ON Message Support.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
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
// 3     3/31/09 4:00p Madhans
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Resources.c
//
// Description:	Library routines to load image resources.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <minisetup.h>

#if TSE_USE_EDK_LIBRARY

#include EFI_PROTOCOL_DEFINITION (FirmwareVolume)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
//#include EFI_PROTOCOL_DEFINITION (HII)
#if PI_SPECIFICATION_VERSION<0x00010000
    EFI_GUID guidFV = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;        //For EDK Library usage tse have to set the fv guids correctly
#else
    EFI_GUID guidFV = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ReadImageResource
//
// Description:	Function to read all the resources of a image.
//
// Input:		EFI_HANDLE ImageHandle, EFI_GUID *pGuid,
//				VOID **ppData, UINTN *pDataSize
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadImageResource(
	EFI_HANDLE ImageHandle, EFI_GUID *pGuid, 
	VOID **ppData, UINTN *pDataSize
)
{
	EFI_STATUS Status;
	EFI_LOADED_IMAGE_PROTOCOL *pImage;
	EFI_FIRMWARE_VOLUME_PROTOCOL *pFV;
	UINTN i=0, DataSize;
	EFI_GUID *pSectionGuid;
	UINT32 Authentication;
      
	Status=gBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, &pImage);
	if (EFI_ERROR(Status)) return Status;
	Status=gBS->HandleProtocol(pImage->DeviceHandle, &guidFV, &pFV);
	if (EFI_ERROR(Status)) return Status;
	do{
		pSectionGuid=NULL;
		DataSize=0;
		Status=pFV->ReadSection (
			pFV,&((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(pImage->FilePath))->NameGuid,
			EFI_SECTION_FREEFORM_SUBTYPE_GUID,i++, &pSectionGuid, &DataSize,
			&Authentication
	 	);
		if (!EFI_ERROR(Status)&&EfiCompareGuid(pSectionGuid,pGuid)) break;
		gBS->FreePool(pSectionGuid);
	}while(!EFI_ERROR(Status));
	if (EFI_ERROR(Status)) return Status;
	*ppData = pSectionGuid;
	if (pDataSize) *pDataSize = DataSize;
	return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FvReadResources 
//
// Description:	Function to read all the section from of specified image.
//
// Input:		  IN EFI_GUID *NameGuid,IN EFI_GUID *pGuid,IN OUT VOID **Buffer,IN OUT UINTN *BufferSize
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FvReadResources (
  IN EFI_GUID                       *NameGuid,
  IN EFI_GUID                       *pGuid, 
  IN OUT VOID                       **Buffer,
  IN OUT UINTN                      *BufferSize
  )
{
	EFI_FIRMWARE_VOLUME_PROTOCOL	*Fv;
    UINT32 AuthenticationStatus;

	EFI_STATUS	Status;
	UINTN		NumHandles;
	EFI_HANDLE	*HandleBuffer;
	UINTN		i,j=0;
	UINTN DataSize=0;
	EFI_GUID *pSectionGuid=NULL;

	Status = gBS->LocateHandleBuffer(ByProtocol,&guidFV,NULL,&NumHandles,&HandleBuffer);
	if (EFI_ERROR(Status)) return Status;

	for (i = 0; i< NumHandles; ++i)
	{
        j=0;
    	gBS->HandleProtocol(HandleBuffer[i],&guidFV,&Fv);
       	do{
    		pSectionGuid=NULL;
    		DataSize=0;
    		Status = Fv->ReadSection(
    			Fv,NameGuid,
    			EFI_SECTION_FREEFORM_SUBTYPE_GUID,j++,
    			&pSectionGuid, &DataSize,
    			&AuthenticationStatus
    		);
            if (!EFI_ERROR(Status)&&EfiCompareGuid(pSectionGuid,pGuid)) break;
    		gBS->FreePool(pSectionGuid);
    	}while(!EFI_ERROR(Status));

    	if (!EFI_ERROR(Status))
        {
            // Section found
            break;
        }
	}
  
    if (!EFI_ERROR(Status))  
    {
    	*Buffer = pSectionGuid;
    	if (BufferSize) *BufferSize = DataSize;
    }

	gBS->FreePool(HandleBuffer);
	return Status;
}


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