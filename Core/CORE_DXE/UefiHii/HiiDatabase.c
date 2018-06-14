//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiiDatabase.c 14    5/21/12 4:55p Artems $
//
// $Revision: 14 $
//
// $Date: 5/21/12 4:55p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiiDatabase.c $
// 
// 14    5/21/12 4:55p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio
// [Files]  		HiiDatabase.c HiiFont.c HiiFontEx.c HiiPrivate.h HiiString.c
// 
// 13    1/05/12 5:05p Artems
// EIP 76735: Font FFS file is not loaded in framework mode, when in
// nested FV
// 
// 12    5/13/11 6:14p Artems
// Renamed functions HiiGetString and HiiSetString to AmiHiiGetString and
// AmiHiiSetString 
// to avoid collusion with EdkII native library functions
// 
// 11    5/05/11 4:13p Artems
// Add signal "layout changed" event if current layout is deleted
// 
// 10    1/05/11 12:41p Artems
// EIP 50995: Added checking of driver handle before adding packages to
// HII database
// 
// 9     6/23/10 5:06p Artems
// Restored fix killed by previous check-in
// 
// 8     6/10/10 4:35p Artems
// EIP 39692 fix - call notification after adding package
// 
// 7     3/09/10 6:41p Artems
// EIP 35698: Removed DeleteSimpleFonts call
// 
// 6     2/03/10 10:28a Artems
// Fixed bug in HiiExportPacks function
// 
// 5     1/29/10 5:43p Artems
// EIP 34553 Updated function ExportPackageLists to support NULL pointer
// as input
// 
// 4     1/07/10 12:29p Felixp
// Code updated to use library instances of the Protocol GUID variables.
// 
// 3     12/04/09 11:16a Artems
// Remove keyboard layout functionality added
// 
// 2     11/09/09 11:51a Felixp
// New package list function is updated to report error when package list
// with existing GUID is passed.
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
// Name:	HiiDatabase.c
//
// Description:	Hii database protocol functions implementation
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#pragma warning (disable : 4090)

#include <AmiDxeLib.h>
#include "HiiPrivate.h"
#include <Protocol/DevicePath.h>
#include <Protocol/HiiUtilities.h>

extern HII_UTILITIES_PROTOCOL HiiUtilitiesProtocol;
extern DBE_KEY_FIELD StringDbKeyField;

EFI_GUID NullGuid = NULL_GUID;

SIMPLE_FONT DefaultFont[0x10000];

HII_DATABASE_PRIVATE_DATA PrivateData = 
{
//Database protocol members
    {   
        HiiNewPack,
        HiiRemovePack,
        HiiUpdatePack,
        HiiListPacks,
        HiiExportPacks,
        HiiRegisterNotify,
        HiiUnregisterNotify,
        HiiFindKeyboardLayouts,
        HiiGetKeyboardLayout,
        HiiSetKeyboardLayout,
        HiiGetPackageListHandle
    },
//String protocol members
    {
        HiiNewString,
        AmiHiiGetString,        //EdkII compatibility library already has function HiiGetString
        AmiHiiSetString,        //EdkII compatibility library already has function HiiSetString
        HiiGetLanguages,
        HiiGetSecondLanguages
    },
//Font protocol members
    {
        HiiStringToImage,
        HiiStringIdToImage,
        HiiGetGlyph,
        HiiGetFontInfo
    },
//Config Routing protocol members
    {
        HiiExtractConfig,
        HiiExportConfig,
        HiiRouteConfig,
        HiiBlockToConfig,
        HiiConfigToBlock,
        HiiGetAltConfig
    },
// Linked list of package lists
	{
		0, 
		NULL,
		NULL
	},
//Linked list of notify functions
	{
		0, 
		NULL,
		NULL
	},
//Linked list of keyboard layouts
	{
		0, 
		NULL,
		NULL
	},
//Linked list of global fonts
	{
		0, 
		NULL,
		NULL
	},
//Current KeyLayout
	NULL
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiDatabaseEntryPoint
//
//  Description:
//  This function is HII driver entry point 
//
//  Input:
// 	IN EFI_HANDLE ImageHandle - Image handle
// 	IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
//  Output:
//  EFI_SUCCESS - Function executed successfully, HII protocols installed
//  EFI_ERROR - Some error occured during execution
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiDriverEntryPoint(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_HANDLE HiiHandle = NULL;

	InitAmiLib(ImageHandle,SystemTable);

	pBS = SystemTable->BootServices;

    //install HII Protocols
	Status = pBS->InstallMultipleProtocolInterfaces(
                    &HiiHandle,            
                    &gEfiHiiDatabaseProtocolGuid,
                    &(PrivateData.DatabaseProtocol),
                    &gEfiHiiStringProtocolGuid,
                    &(PrivateData.StringProtocol),
                    &gEfiHiiFontProtocolGuid,
                    &(PrivateData.FontProtocol),
                    &gEfiHiiConfigRoutingProtocolGuid,
                    &(PrivateData.ConfigRoutingProtocol),
                    &gHiiUtilitiesProtocolGuid, 
                    &HiiUtilitiesProtocol,
                    NULL);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiBdsEntryPoint
//
//  Description:
//  This function is HII driver BDS entry point 
//
//  Input:
// 	IN EFI_HANDLE ImageHandle - Image handle
// 	IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
//  Output:
//  EFI_SUCCESS - Function executed successfully, system font is loaded
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiBdsEntryPoint(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_HANDLE HiiHandle = NULL;

	InitAmiLib(ImageHandle,SystemTable);
    Status = LoadSystemFont();

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiGetPackHandle
//
//  Description:
//  This function is HII Database protocol function GetPackageHandle implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
// 	IN EFI_HII_HANDLE PackageListHandle - PackageList handle
//  OUT EFI_HANDLE *DriverHandle - Pointer, where to store found Driver handle
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - PackageListHandle is invalid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiGetPackageListHandle (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN EFI_HII_HANDLE                       PackageListHandle,
    OUT EFI_HANDLE                          *DriverHandle)
{
	PACKAGE_LIST_RECORD *Record;

	Record = (PACKAGE_LIST_RECORD *) PackageListHandle;

    if (DriverHandle == NULL)
        return EFI_INVALID_PARAMETER;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_INVALID_PARAMETER;

	*DriverHandle = Record->DriverHandle;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiRegisterNotify
//
//  Description:
//  This function is HII Database protocol function RegisterPackageNotify implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
// 	IN UINT8 PackageType - Package type
//  IN EFI_GUID *PackageGuid - Pointer to Package guid
//  IN EFI_HII_DATABASE_NOTIFY PackageNotifyFn - Function to be called
//  IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType - Notify type
//  OUT EFI_HANDLE *NotifyHandle - Pointer, where to store created Notify handle
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - PackageGuid is not NULL and PackageType is not Guid package
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiRegisterNotify (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN UINT8                                PackageType,
    IN CONST EFI_GUID                       *PackageGuid,
    IN CONST EFI_HII_DATABASE_NOTIFY        PackageNotifyFn,
    IN EFI_HII_DATABASE_NOTIFY_TYPE         NotifyType,
    OUT EFI_HANDLE                          *NotifyHandle)
{
	NOTIFY_RECORD *NewRecord;

    if (NotifyHandle == NULL)
        return EFI_INVALID_PARAMETER;

    if ((PackageType == EFI_HII_PACKAGE_TYPE_GUID && PackageGuid == NULL) ||
        (PackageType != EFI_HII_PACKAGE_TYPE_GUID && PackageGuid != NULL))
        return EFI_INVALID_PARAMETER;

	NewRecord = NewNotifyRecord();
	if (NewRecord == NULL)
		return EFI_OUT_OF_RESOURCES;

	if(PackageType == EFI_HII_PACKAGE_TYPE_GUID)
		NewRecord->PackageGuid =  *PackageGuid;
	else
		NewRecord->PackageGuid = NullGuid;

	NewRecord->PackageType = PackageType;
	NewRecord->NotifyType  = NotifyType;
	NewRecord->PackageNotifyFn = PackageNotifyFn;

	DListAdd(&(PrivateData.NotifyList), (DLINK *) NewRecord);

	if(NotifyHandle != NULL)
		*NotifyHandle = NewRecord;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiUnregisterNotify
//
//  Description:
//  This function is HII Database protocol function UnregisterPackageNotify implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_HANDLE NotificationHandle - Notify handle
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - NotificationHandle is not valid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiUnregisterNotify (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HANDLE                           NotificationHandle)
{
	NOTIFY_RECORD *Record;

	Record = (NOTIFY_RECORD *) NotificationHandle;

	if (Record->Signature != NOTIFY_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;

	DListDelete(&(PrivateData.NotifyList), (DLINK *) Record);
    Record->Signature = 0xffffffff;         //invalidate signature to avoid future use of this memory
	pBS->FreePool(Record);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiRemovePack
//
//  Description:
//  This function is HII Database protocol function RemovePackageList implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_HII_HANDLE Handle - Handle of package list to be removed from database
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - Handle is not valid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiRemovePack (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle)
{
    PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *) Handle;
	PACKAGE_LINK *Package;
	PACKAGE_LINK *Link;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;

	Package = (PACKAGE_LINK *) Record->PackageList.pHead;

	while(Package != NULL)
	{
		Link = Package;
		Package = (PACKAGE_LINK *) Package->Link.pNext;
		RemovePackage(Handle, Link);
	}

	DListDelete(&(PrivateData.PackList), (DLINK *) Record);
    Record->Signature = 0xffffffff;     //invalidate signature to avoid future collisions
	pBS->FreePool(Record);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiNewPack
//
//  Description:
//  This function is HII Database protocol function NewPackageList implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_HII_PACKAGE_LIST_HEADER *PackageList - Pointer to package list to be added to database
//  IN EFI_HANDLE DriverHandle - Driver handle
//  OUT EFI_HII_HANDLE *Handle - Pointer to EFI_HII_HANDLE where to store created handle
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - Handle or PackageList is NULL
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiNewPack (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList,
    IN CONST EFI_HANDLE                     DriverHandle,
    OUT EFI_HII_HANDLE                      *Handle)
{
	PACKAGE_LIST_RECORD *NewRecord;
	EFI_STATUS Status;
	EFI_DEVICE_PATH_PROTOCOL *DpProtocol;
	UINT32 DpPackageSize;
	EFI_HII_PACKAGE_HEADER *Buffer;

	if((PackageList == NULL) || (Handle == NULL))
        return EFI_INVALID_PARAMETER;

    // Check the Package list GUID and DriverHandle to guarantee this GUID is unique in database.
	if(CheckIfPresent(&(PackageList->PackageListGuid), DriverHandle))
		return EFI_ALREADY_STARTED;								//package list already present

	NewRecord = NewPackageListRecord();
	if(NewRecord == NULL)
		return EFI_OUT_OF_RESOURCES;

	NewRecord->DriverHandle = DriverHandle;
	NewRecord->Guid = PackageList->PackageListGuid;

	Status = AddPackages((EFI_HII_HANDLE)NewRecord, PackageList, FALSE);
	if(EFI_ERROR(Status) && (NewRecord->PackageList.Size != 0))
	{
		DeleteList(&(NewRecord->PackageList));
		pBS->FreePool(NewRecord);
		return EFI_OUT_OF_RESOURCES;
	}


    Status = pBS->HandleProtocol(DriverHandle, &gEfiDevicePathProtocolGuid, &DpProtocol);
    if(!EFI_ERROR(Status))
    {
        DpPackageSize = (UINT32)DPLength(DpProtocol);
		Status = pBS->AllocatePool(
			                    EfiBootServicesData, 
								DpPackageSize + sizeof(EFI_HII_PACKAGE_HEADER), 
								&Buffer);
		if (EFI_ERROR(Status))
		{
			DeleteList(&(NewRecord->PackageList));
			pBS->FreePool(NewRecord);
			return EFI_OUT_OF_RESOURCES;
		}

		Buffer->Type = EFI_HII_PACKAGE_DEVICE_PATH;
		Buffer->Length = DpPackageSize + sizeof(EFI_HII_PACKAGE_HEADER);

		(UINT8 *)Buffer += sizeof(EFI_HII_PACKAGE_HEADER);
		MemCpy(Buffer, DpProtocol, DpPackageSize);
		(UINT8 *)Buffer -= sizeof(EFI_HII_PACKAGE_HEADER);

		Status = AddPackage((EFI_HII_HANDLE)NewRecord, Buffer, EFI_HII_DATABASE_NOTIFY_NEW_PACK);
		if (EFI_ERROR(Status))
		{
			DeleteList(&(NewRecord->PackageList));
			pBS->FreePool(NewRecord);
			return EFI_OUT_OF_RESOURCES;
		}
		pBS->FreePool(Buffer);
    }

	DListAdd(&(PrivateData.PackList), (DLINK *)NewRecord);
	*Handle = NewRecord;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiListPacks
//
//  Description:
//  This function is HII Database protocol function ListPackageLists implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
// 	IN UINT8 PackageType - Package type
//  IN EFI_GUID *PackageGuid - Pointer to package guid
//  IN OUT UINTN *HandleBufferLength - Pointer to allocated buffer size value
//  OUT EFI_HII_HANDLE *Handle - Pointer to EFI_HII_HANDLE buffer where to store found handles
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - HandleBufferLength is NULL
//  EFI_BUFFER_TOO_SMALL - Allocated buffer too small
//  EFI_NOT_FOUND - No handles found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiListPacks (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN UINT8                                PackageType,
    IN CONST EFI_GUID                       *PackageGuid,
    IN OUT UINTN                            *HandleBufferLength,
    OUT EFI_HII_HANDLE                      *Handle)
{
    UINTN RequiredSize = 0;
    UINT32 i, Count = 0;
    EFI_STATUS Status;
	PACKAGE_LIST_RECORD *List;
	BOOLEAN InternalBuffer = TRUE;
	BOOLEAN Found;
	EFI_HII_HANDLE *MatchedHandles;

    if(HandleBufferLength == NULL)
        return EFI_INVALID_PARAMETER;

    if (*HandleBufferLength > 0 && Handle == NULL)
        return EFI_INVALID_PARAMETER;

    if ((PackageType == EFI_HII_PACKAGE_TYPE_GUID && PackageGuid == NULL) ||
        (PackageType != EFI_HII_PACKAGE_TYPE_GUID && PackageGuid != NULL))
        return EFI_INVALID_PARAMETER;

	List = (PACKAGE_LIST_RECORD *)(PrivateData.PackList.pHead);

    if(PackageType == EFI_HII_PACKAGE_TYPE_ALL)
    {
		RequiredSize = sizeof(EFI_HII_HANDLE) * PrivateData.PackList.Size;

        if(*HandleBufferLength < RequiredSize)
        {
            *HandleBufferLength = RequiredSize;
            return EFI_BUFFER_TOO_SMALL;
        }

		for(i = 0; i < PrivateData.PackList.Size; i++)
		{
            Handle[i] = List;
			List = (PACKAGE_LIST_RECORD *)List->Link.pNext;
		}
    }
    else
    {
        Status = pBS->AllocatePool(
                            EfiBootServicesData, 
                            sizeof(EFI_HII_HANDLE) * PrivateData.PackList.Size, 
                            (VOID **)&MatchedHandles);
        if(EFI_ERROR(Status))
            InternalBuffer = FALSE;

        //parsing package lists to find matches. If internal buffer present found handles will be
        //stored to avoid repeat parsing
        for(i = 0; i < PrivateData.PackList.Size; i++)
        {
            Found = FindAndRemovePackages(
									(EFI_HII_HANDLE)List,
									PackageType,
									PackageGuid,
									TRUE);
            if(Found)
			{
	            if(InternalBuffer)
					MatchedHandles[Count] = (EFI_HII_HANDLE)List;
				Count++;
			}
			List = (PACKAGE_LIST_RECORD *) List->Link.pNext;
        }

        if(Count == 0)
            return EFI_NOT_FOUND;

        RequiredSize = Count * sizeof(EFI_HII_HANDLE);

        if(*HandleBufferLength < RequiredSize)
        {
            *HandleBufferLength = RequiredSize;
            return EFI_BUFFER_TOO_SMALL;
        }

        if(InternalBuffer)
        {
            for(i = 0; i < Count; i++)
                Handle[i] = MatchedHandles[i];
            pBS->FreePool(MatchedHandles);
        }
        else
        {
            Count = 0;
            for(i = 0; i < PrivateData.PackList.Size; i++)
            {
				Found = FindAndRemovePackages(
									(EFI_HII_HANDLE)List,
									PackageType,
									PackageGuid,
									TRUE);
                if(Found)
                {
                    Handle[Count] = (EFI_HII_HANDLE)List;
                    Count++;
                }
				List = (PACKAGE_LIST_RECORD *) List->Link.pNext;
            }
        }
    }

    *HandleBufferLength = RequiredSize;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiUpdatePack
//
//  Description:
//  This function is HII Database protocol function UpdatePackageList implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_HII_HANDLE Handle - Handle of package list to be updated
//  IN EFI_HII_PACKAGE_LIST_HEADER *PackageList - Pointer to new Package list
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - Handle is invalid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiUpdatePack (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle,
    IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList)
{
    PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *) Handle;
	EFI_STATUS Status;

    if (PackageList == NULL)
        return EFI_INVALID_PARAMETER;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE)
		return EFI_NOT_FOUND;
	
	Status = AddPackages(Handle, PackageList, TRUE);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiExportPacks
//
//  Description:
//  This function is HII Database protocol function ExportPackageLists implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_HII_HANDLE Handle - Handle of package list to be exported
//  IN OUT UINTN *BufferSize - Pointer to export buffer size value
//  OUT EFI_HII_PACKAGE_LIST_HEADER *Buffer - Pointer to buffer where to export package lists
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - Handle is invalid
//  EFI_BUFFER_TOO_SMALL - Export buffer too small
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiExportPacks (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle,
    IN OUT UINTN                            *BufferSize,
    OUT EFI_HII_PACKAGE_LIST_HEADER         *Buffer)
{
    EFI_STATUS Status;
    PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *) Handle;
    UINT32 Size = 0;
    UINTN PackageListSize;
    UINTN RequiredSize = 0;
    UINTN MaxPackageListSize = 0;
    VOID *IntBuffer;

//Conformance check, as required by SCT
    if (BufferSize == NULL)
       return EFI_INVALID_PARAMETER;

    if (*BufferSize > 0 && Buffer == NULL)
        return EFI_INVALID_PARAMETER;
//End of conformace check

	if (Record != NULL) //we need to export only specific package list
		return ExportPack(Handle, BufferSize, Buffer, TRUE);

//we need to return all package lists
	Record = (PACKAGE_LIST_RECORD *)(PrivateData.PackList.pHead);

	while(Record != NULL) {
        //first determine required buffer size
        PackageListSize = 0;
        Status = ExportPack((EFI_HII_HANDLE)Record, &PackageListSize, NULL, TRUE);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            RequiredSize += PackageListSize;
            MaxPackageListSize = (MaxPackageListSize > PackageListSize) ? MaxPackageListSize : PackageListSize;
        }
		Record = (PACKAGE_LIST_RECORD *)(Record->Link.pNext);
	}

    if(*BufferSize < RequiredSize) {
        *BufferSize = RequiredSize;
        return EFI_BUFFER_TOO_SMALL;
    }

    Status = pBS->AllocatePool(EfiBootServicesData, MaxPackageListSize, &IntBuffer);
    if(EFI_ERROR(Status))
        return Status;

	Record = (PACKAGE_LIST_RECORD *)(PrivateData.PackList.pHead);

	while(Record != NULL) {
        //export all package lists one by one
        PackageListSize = MaxPackageListSize;
        Status = ExportPack((EFI_HII_HANDLE)Record, &PackageListSize, IntBuffer, FALSE);
        if(!EFI_ERROR(Status)) {
            MemCpy(Buffer, IntBuffer, PackageListSize);
            (UINT8 *)Buffer += PackageListSize;
        }
		Record = (PACKAGE_LIST_RECORD *)(Record->Link.pNext);
	}

    pBS->FreePool(IntBuffer);
    *BufferSize = RequiredSize;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiFindKeyboardLayouts
//
//  Description:
//  This function is HII Database protocol function FindKeyboardLayouts implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN OUT UINT16 *KeyGuidBufferLength - Pointer to allocated buffer size value
//  OUT EFI_GUID *KeyGuidBuffer - Pointer to EFI_GUID buffer where to store found layouts
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - KeyGuidBufferLength or KeyGuidBuffer is NULL
//  EFI_BUFFER_TOO_SMALL - Allocated buffer too small
//  EFI_NOT_FOUND - No layouts found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiFindKeyboardLayouts (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN OUT UINT16                           *KeyGuidBufferLength,
    OUT EFI_GUID                            *KeyGuidBuffer)
{
	UINT16 RequiredSize;
	KEY_LAYOUT_LINK *Link;
	UINT16 i;

	if(KeyGuidBufferLength == NULL || KeyGuidBuffer == NULL)
		return EFI_INVALID_PARAMETER;

	if(PrivateData.KeyLayoutList.Size == 0)
		return EFI_NOT_FOUND;

	RequiredSize = (UINT16) PrivateData.KeyLayoutList.Size * sizeof(EFI_GUID);
	if(RequiredSize > *KeyGuidBufferLength)
	{
		*KeyGuidBufferLength = RequiredSize;
		return EFI_BUFFER_TOO_SMALL;
	}

	Link = (KEY_LAYOUT_LINK *)PrivateData.KeyLayoutList.pHead;
	for(i = 0; i < PrivateData.KeyLayoutList.Size; i++)
	{
		KeyGuidBuffer[i] = Link->Layout.Guid;
		Link = (KEY_LAYOUT_LINK *) Link->Link.pNext;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiSetKeyboardLayout
//
//  Description:
//  This function is HII Database protocol function SetKeyboardLayout implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_GUID *KeyGuid - Pointer to EFI_GUID of layout to set
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - KeyGuid is NULL
//  EFI_NOT_FOUND - Given layout not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//dummy function for signal event procedure
VOID SetKbLayoutNotifyFn(IN EFI_EVENT Event, IN VOID *Context) {}

EFI_STATUS HiiSetKeyboardLayout (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN EFI_GUID                             *KeyGuid)
{
	EFI_HII_KEYBOARD_LAYOUT* Layout;
    EFI_STATUS Status;

	if(KeyGuid == NULL)
		return EFI_INVALID_PARAMETER;

	Layout = FindLayoutByGuid(KeyGuid);
	if(Layout == NULL)
		return EFI_NOT_FOUND;

	PrivateData.CurrentLayout = Layout;
    Status = SignalKbLayoutChangedEvent();

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiGetKeyboardLayout
//
//  Description:
//  This function is HII Database protocol function GetKeyboardLayout implementation 
//
//  Input:
// 	IN EFI_HII_DATABASE_PROTOCOL *This - Pointer to EFI_HII_DATABASE_PROTOCOL structure
//  IN EFI_GUID *KeyGuid - Pointer to EFI_GUID of layout to set
//  IN OUT UINT16 *KeyGuidBufferLength - Pointer to allocated buffer size value
//  OUT EFI_HII_KEYBOARD_LAYOUT *KeyboardLayout - Pointer to EFI_HII_KEYBOARD_LAYOUT where to store layout
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_INVALID_PARAMETER - KeyboardLayout or KeyGuidBufferLength is NULL
//  EFI_NOT_FOUND - Given layout not found
//  EFI_BUFFER_TOO_SMALL - Allocated buffer too small
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiGetKeyboardLayout (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN EFI_GUID                             *KeyGuid,
    IN OUT UINT16                           *KeyGuidBufferLength,
    OUT EFI_HII_KEYBOARD_LAYOUT             *KeyboardLayout)
{
	EFI_HII_KEYBOARD_LAYOUT *Layout;

	if(KeyGuidBufferLength == NULL)
		return EFI_INVALID_PARAMETER;

	if(*KeyGuidBufferLength != 0 && KeyboardLayout == NULL)
		return EFI_INVALID_PARAMETER;

	if(KeyGuid == NULL)
		Layout = PrivateData.CurrentLayout;
	else
		Layout = FindLayoutByGuid(KeyGuid);

	if(Layout == NULL)
		return EFI_NOT_FOUND;

	if(Layout->LayoutLength > *KeyGuidBufferLength)
	{
		*KeyGuidBufferLength = Layout->LayoutLength;
		return EFI_BUFFER_TOO_SMALL;
	}

	MemCpy(KeyboardLayout, Layout, Layout->LayoutLength);
	return EFI_SUCCESS;
}

//********************** Service functions implementation ***************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddPackages
//
//  Description:
//  This function adds packages from PackageList to package list with given handle
//
//  Input:
// 	IN EFI_HII_HANDLE Handle - Handle of package list where to add packages
//  IN EFI_HII_PACKAGE_LIST_HEADER *PackageList - Pointer to package list which packages to add
//  IN BOOLEAN Update - Flag which defines packages should be added or updated
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_ERROR - Some error occured during execution
//
//  Notes:
//  If Update is TRUE control flow goes as described in UpdatePackageList function definition (see UEFI
//  specification v2.1) Otherwise control flow goes as described in NewPackageList function definition
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddPackages(
    IN EFI_HII_HANDLE				Handle,
	IN EFI_HII_PACKAGE_LIST_HEADER *PackageList,
	BOOLEAN							Update)
{
	UINT8		 Passes;
	EFI_GUID	 *Guid;
	UINT8		 PackageType;
	EFI_STATUS	 Status;
	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType;
	EFI_HII_PACKAGE_LIST_HEADER  *SavePointer;
	UINT32 ControlSize;

	SavePointer = PackageList;
	ControlSize = PackageList->PackageLength;

	if(Update)
	{
		Passes = 2;		//set number of passes
		NotifyType = EFI_HII_DATABASE_NOTIFY_ADD_PACK;
	}
	else
	{
		Passes = 1;		//set number of passes
		NotifyType = EFI_HII_DATABASE_NOTIFY_NEW_PACK;
	}

	while(Passes--)
	{
		(UINT8 *)PackageList += sizeof(EFI_HII_PACKAGE_LIST_HEADER);
		ControlSize -= sizeof(EFI_HII_PACKAGE_LIST_HEADER);

		while(((EFI_HII_PACKAGE_HEADER *)PackageList)->Type != EFI_HII_PACKAGE_END && ControlSize > 0)
		{
			if(Update)
			{
				PackageType = ((EFI_HII_PACKAGE_HEADER *)PackageList)->Type;
				if(PackageType == EFI_HII_PACKAGE_TYPE_GUID)
					Guid = (EFI_GUID *) &(((EFI_HII_GUID_PACKAGE_HDR *)PackageList)->Guid);
				else
					Guid = NULL;
				FindAndRemovePackages(Handle, PackageType, Guid, FALSE);
			}
			else
			{
				Status = AddPackage(Handle, (EFI_HII_PACKAGE_HEADER *)PackageList, NotifyType);
				if(EFI_ERROR(Status))
					return Status;
			}

            ControlSize -= ((EFI_HII_PACKAGE_HEADER *)PackageList)->Length;
			(UINT8 *)PackageList += ((EFI_HII_PACKAGE_HEADER *)PackageList)->Length;
		}
		Update = FALSE;
		PackageList = SavePointer;
		ControlSize = PackageList->PackageLength;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddPackage
//
//  Description:
//  This function adds package to package list with given handle
//
//  Input:
// 	IN EFI_HII_HANDLE Handle - Handle of package list where to add package
//  IN EFI_HII_PACKAGE_HEADER *Package - Pointer to package to add
//  IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType - Notify type to be signalled
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_ERROR - Some error occured during execution
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddPackage(
    IN EFI_HII_HANDLE            Handle,
	IN EFI_HII_PACKAGE_HEADER    *Package,
	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType)
{
	PACKAGE_LINK *NewLink;
	UINT32		 Size;
	DLIST		 *PackageList;
	EFI_STATUS	 Status = EFI_SUCCESS;

	PackageList = &(((PACKAGE_LIST_RECORD *)Handle)->PackageList);

	Size = Package->Length;
	NewLink = (PACKAGE_LINK *) CreateNewLink(Size);
	if(NewLink == NULL)
		return EFI_OUT_OF_RESOURCES;
	MemCpy(&(NewLink->Package), Package, Size);

	switch(Package->Type)
	{
		case EFI_HII_PACKAGE_STRINGS:
			Status = ParseStringsPackage(
							(PACKAGE_LIST_RECORD *)Handle,
							(EFI_HII_STRING_PACKAGE_HDR *)Package);
			break;
		case EFI_HII_PACKAGE_SIMPLE_FONTS:
			Status = ParseSimpleFontsPackage((EFI_HII_SIMPLE_FONT_PACKAGE_HDR *)Package);
			break;
		case EFI_HII_PACKAGE_FONTS:
			Status = ParseFontsPackage((EFI_HII_FONT_PACKAGE_HDR *)Package);
			break;
		case EFI_HII_PACKAGE_KEYBOARD_LAYOUT:
			Status = ParseKeyLayoutPackage((EFI_HII_KEYBOARD_PACKAGE_HDR *)Package);
			break;
		default:
			break;
	}

	if(EFI_ERROR(Status))
		return Status;

	DListAdd(PackageList, (DLINK *)NewLink);

	if(PrivateData.NotifyList.Size > 0)
		InvokeRegisteredNotify(Package, Handle, NotifyType);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindAndRemovePackages
//
//  Description:
//  This function finds or removes packages from package list with given handle
//
//  Input:
// 	IN EFI_HII_HANDLE Handle - Handle of package list where to find package
// 	IN UINT8 PackageType - Package type to find
//  IN EFI_GUID *PackageGuid - Pointer to package guid to find
//  IN BOOLEAN FindOnly - Flag, which determines should package be found or removed
//
//  Output:
//  TRUE - Package of given type found
//
//  Notes:
//  If FindOnly is TRUE, function returns TRUE when first package of given type is found. Otherwise
//  function removes all packages of given type from package list and returns FALSE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FindAndRemovePackages (
    IN EFI_HII_HANDLE  Handle,
    IN UINT8           PackageType,
    IN CONST EFI_GUID  *PackageGuid,
	IN BOOLEAN		   FindOnly )
{
	DLIST		 *PackageList;
	PACKAGE_LINK *Link;
	PACKAGE_LINK *FoundLink;


	PackageList = &(((PACKAGE_LIST_RECORD *)Handle)->PackageList);
	Link = (PACKAGE_LINK *)(PackageList->pHead);

	while(Link != NULL)
	{
		if(MatchPackage(PackageType, PackageGuid, &(Link->Package)))
		{
			if(FindOnly)
				return TRUE;
			else
			{
				FoundLink = Link;
				Link = (PACKAGE_LINK *)Link->Link.pPrev;
				RemovePackage(Handle, FoundLink);
			}
		}
		if(Link == NULL) //we removed first element from list
			Link = (PACKAGE_LINK *)(PackageList->pHead);
		else
			Link = (PACKAGE_LINK *)Link->Link.pNext;
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   RemovePackage
//
//  Description:
//  This function removes package from package list with given handle
//
//  Input:
// 	IN EFI_HII_HANDLE Handle - Handle of package list where to add package
//  IN PACKAGE_LINK *Package - Pointer to package to remove
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RemovePackage (
    IN EFI_HII_HANDLE Handle,
    IN PACKAGE_LINK   *Package )
{
	DLIST		 *PackageList;

	PackageList = &(((PACKAGE_LIST_RECORD *)Handle)->PackageList);

	if(PrivateData.NotifyList.Size > 0)
		InvokeRegisteredNotify(&(Package->Package), Handle, EFI_HII_DATABASE_NOTIFY_REMOVE_PACK);

	switch(Package->Package.Type)
	{
		case EFI_HII_PACKAGE_STRINGS:
            DeleteStringsFromDatabase(&(((PACKAGE_LIST_RECORD *)Handle)->StringDb));
            DeleteList(&(((PACKAGE_LIST_RECORD *)Handle)->LanguageList));
			break;
		case EFI_HII_PACKAGE_SIMPLE_FONTS:
//            DeleteSimpleFonts((EFI_HII_SIMPLE_FONT_PACKAGE_HDR *)&(Package->Package));
			break;
		case EFI_HII_PACKAGE_FONTS:
//            DeleteFonts((EFI_HII_FONT_PACKAGE_HDR *)&(Package->Package));
			break;
        case EFI_HII_PACKAGE_KEYBOARD_LAYOUT:
            DeleteKeyboardLayout((EFI_HII_KEYBOARD_PACKAGE_HDR *)&(Package->Package));
            break;
		default:
			break;
	}
	DListDelete(PackageList, (DLINK *)Package);
	pBS->FreePool(Package);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   InvokeRegisteredNotify
//
//  Description:
//  This function invokes registered notify function if package types match
//
//  Input:
//  IN EFI_HII_PACKAGE_HEADER *Package - Pointer to package to match
// 	IN EFI_HII_HANDLE Handle - Handle of package list to whom given package belongs
//  IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType - Notification type
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InvokeRegisteredNotify (
    IN EFI_HII_PACKAGE_HEADER		*Package,
    IN EFI_HII_HANDLE               Handle,
    IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType)
{
	NOTIFY_RECORD *Record;

	Record = (NOTIFY_RECORD *)(PrivateData.NotifyList.pHead);

	while(Record != NULL)
	{
		if(MatchPackage(Record->PackageType, &(Record->PackageGuid), Package) &&
		  (NotifyType & Record->NotifyType))
			Record->PackageNotifyFn(Record->PackageType, 
									&(Record->PackageGuid), 
									Package,
									Handle,
									NotifyType);
		Record = (NOTIFY_RECORD *)(Record->Link.pNext);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   NewPackageListRecord
//
//  Description:
//  This function creates new PACKAGE_LIST_RECORD structure and returns pointer to it
//
//  Input:
//  None
//
//  Output:
//  PACKAGE_LIST_RECORD* - pointer to newly created structure
//  NULL - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PACKAGE_LIST_RECORD* NewPackageListRecord(	VOID )
{
	EFI_STATUS Status;
	PACKAGE_LIST_RECORD *Record;

	Status = pBS->AllocatePool(
                    EfiBootServicesData, 
					sizeof(PACKAGE_LIST_RECORD), 
					&Record);
	if (EFI_ERROR(Status))
		return NULL;

	Record->Signature = PACKAGE_LIST_RECORD_SIGNATURE;

	DListInit(&(Record->PackageList));
	DListInit(&(Record->LanguageList));
	DListInit(&(Record->StringFontList));

	Record->StringDb.InitialCount = 20;
	Record->StringDb.RecordCount = 0;
	Record->StringDb.KeyField = &StringDbKeyField;
	Record->StringDb.MemoryType = EfiBootServicesData;
	Record->StringDb.KeyCount = 1;
	
	Status = pBS->AllocatePool(
                    EfiBootServicesData, 
					sizeof(VOID *) * 20, 
					&(Record->StringDb.IndexArray));

	if (EFI_ERROR(Status))
	{
		pBS->FreePool(Record);
		return NULL;
	}

	return Record;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   NewNotifyRecord
//
//  Description:
//  This function creates new NOTIFY_RECORD structure and returns pointer to it
//
//  Input:
//  None
//
//  Output:
//  NOTIFY_RECORD* - pointer to newly created structure
//  NULL - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
NOTIFY_RECORD* NewNotifyRecord(	VOID )
{
	EFI_STATUS Status;
	NOTIFY_RECORD *Record;

	Status = pBS->AllocatePool(
                    EfiBootServicesData, 
					sizeof(NOTIFY_RECORD), 
					&Record);
	if (EFI_ERROR(Status))
		return NULL;

	Record->Signature = NOTIFY_LIST_RECORD_SIGNATURE;

	return Record;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CreateNewLink
//
//  Description:
//  This function creates new link structure for linked list and returns pointer to it
//
//  Input:
//  IN UINT32 Size - size of the link stucture in bytes
//
//  Output:
//  VOID* - pointer to newly created structure
//  NULL - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* CreateNewLink(UINT32 Size)
{
	EFI_STATUS Status;
	VOID *Buffer;

	Status = pBS->AllocatePool(
                    EfiBootServicesData, 
					Size + sizeof(DLINK), 
					&Buffer);
	if (EFI_ERROR(Status))
		return NULL;

	return Buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DeleteList
//
//  Description:
//  This function deletes linked list and frees allocated memory
//
//  Input:
//  IN DLIST *List - Pointer to linked list to be deleted
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DeleteList(DLIST *List)
{
	DLINK *Current;
	DLINK *Next;

	Current = List->pHead;

	while(Current != NULL)
	{
		Next = Current->pNext;
		pBS->FreePool(Current);
		Current = Next;
	}

	List->pHead = NULL;
	List->pTail = NULL;
	List->Size = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   MatchPackage
//
//  Description:
//  This function checks if given package matches given type and guid
//
//  Input:
//  IN UINT8 PackageType - Package type to match
//  IN EFI_GUID *PackageGuid - Pointer to package guid to match
//  IN EFI_HII_PACKAGE_HEADER *Package - Pointer to package to check
//
//  Output:
//  TRUE - package matches given type and guid
//  FALSE - package don't match
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchPackage(
    IN UINT8                  PackageType,
    IN EFI_GUID               *PackageGuid,
    IN EFI_HII_PACKAGE_HEADER *Package)
{
    if(PackageType != Package->Type)
		return FALSE;

	if(PackageType == EFI_HII_PACKAGE_TYPE_GUID)
	{
		if(guidcmp(PackageGuid, &(((EFI_HII_GUID_PACKAGE_HDR *)Package)->Guid)))
			return FALSE;
	}
	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CheckIfPresent
//
//  Description:
//  This function checks if package list with given guid already in database
//
//  Input:
//  IN EFI_GUID *Guid - Pointer to package list guid to check
//  IN EFI_HANDLE DriverHandle - Driver handle
//
//  Output:
//  TRUE - package list already present in database
//  FALSE - package list with given guid not found in database
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckIfPresent(
    IN EFI_GUID *Guid, 
    IN EFI_HANDLE DriverHandle)
{
	PACKAGE_LIST_RECORD *Record;

	Record = (PACKAGE_LIST_RECORD *)(PrivateData.PackList.pHead);

	while(Record != NULL)
	{
		if((!guidcmp(Guid, &(Record->Guid))) && (DriverHandle == Record->DriverHandle))
			return TRUE;
		Record = (PACKAGE_LIST_RECORD *)(Record->Link.pNext);
	}

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ParseKeyLayoutPackage
//
//  Description:
//  This function extracts keyboard layout from package and saves it in private area
//
//  Input:
//  IN EFI_HII_KEYBOARD_PACKAGE_HDR *Package - Pointer to keyboard layout package 
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseKeyLayoutPackage(
	IN EFI_HII_KEYBOARD_PACKAGE_HDR *Package)
{
	KEY_LAYOUT_LINK *Link;
	UINT16 i;
	UINT8 *Pointer;
	UINT32 Size;

	Pointer = (UINT8 *)Package;
	Pointer += sizeof(EFI_HII_KEYBOARD_PACKAGE_HDR);

	for(i = 0; i < Package->LayoutCount; i++)
	{
		Size = ((EFI_HII_KEYBOARD_LAYOUT *)Pointer)->LayoutLength;
		Link = (KEY_LAYOUT_LINK *) CreateNewLink(Size);
		if(Link == NULL)
			return EFI_OUT_OF_RESOURCES;
		MemCpy(&(Link->Layout), Pointer, Size);
		DListAdd(&(PrivateData.KeyLayoutList), (DLINK *)Link);
		Pointer += Size;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DeleteKeyboardLayout
//
//  Description:
//  This function removes keyboard layouts existing in package from HII database
//
//  Input:
//  IN EFI_HII_KEYBOARD_PACKAGE_HDR *Package - Pointer to keyboard layout package 
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DeleteKeyboardLayout(
	IN EFI_HII_KEYBOARD_PACKAGE_HDR *Package)
{
	KEY_LAYOUT_LINK *Link;
	UINT16 i;
	UINT8 *Pointer;
	UINT32 Size;

	Pointer = (UINT8 *)Package;
	Pointer += sizeof(EFI_HII_KEYBOARD_PACKAGE_HDR);

	for(i = 0; i < Package->LayoutCount; i++)
	{
        Size = ((EFI_HII_KEYBOARD_LAYOUT *)Pointer)->LayoutLength;
	    Link = (KEY_LAYOUT_LINK *)PrivateData.KeyLayoutList.pHead;
	    while(Link != NULL)
	    {
		    if(!guidcmp(&(((EFI_HII_KEYBOARD_LAYOUT *)Pointer)->Guid), &(Link->Layout.Guid)))
			    break;
		    Link = (KEY_LAYOUT_LINK *)Link->Link.pNext;
	    }
    
        if(Link != NULL) {
            if(PrivateData.CurrentLayout == &(Link->Layout)) {
                PrivateData.CurrentLayout = NULL;
                SignalKbLayoutChangedEvent();
            }

		    DListDelete(&(PrivateData.KeyLayoutList), (DLINK *)Link);
        }
		Pointer += Size;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindLayoutByGuid
//
//  Description:
//  This function finds keyboard layout in private area by given guid
//
//  Input:
//  IN EFI_GUID *Guid - Pointer to guid of keyboard layout 
//
//  Output:
//  EFI_HII_KEYBOARD_LAYOUT* - Pointer to found layout
//  NULL - layout not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HII_KEYBOARD_LAYOUT* FindLayoutByGuid(
	IN EFI_GUID *Guid)
{
	KEY_LAYOUT_LINK *Link;

	Link = (KEY_LAYOUT_LINK *)PrivateData.KeyLayoutList.pHead;
	while(Link != NULL)
	{
		if(!guidcmp(Guid, &(Link->Layout.Guid)))
			return &(Link->Layout);
		Link = (KEY_LAYOUT_LINK *)Link->Link.pNext;
	}
	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ParseSimpleFontsPackage
//
//  Description:
//  This function extracts simple fonts from package and saves in private area
//
//  Input:
//  IN EFI_HII_SIMPLE_FONT_PACKAGE_HDR *Package - Pointer to simple font package 
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseSimpleFontsPackage(
	IN EFI_HII_SIMPLE_FONT_PACKAGE_HDR *Package)
{
	EFI_STATUS Status;
	UINT16 i;
	UINT16 Symbol;
	EFI_NARROW_GLYPH *NGlyph;
	EFI_WIDE_GLYPH *WGlyph;

	NGlyph = Package->NarrowGlyphs;
	WGlyph = (EFI_WIDE_GLYPH *)NGlyph;
	(UINT8 *)WGlyph += Package->NumberOfNarrowGlyphs * sizeof(EFI_NARROW_GLYPH);

	for(i = 0; i < Package->NumberOfNarrowGlyphs; i++)
	{
		Symbol = NGlyph[i].UnicodeWeight;
		if(DefaultFont[Symbol].NarrowGlyph == NULL)
		{
			Status = pBS->AllocatePool(
								EfiBootServicesData, 
								sizeof(EFI_NARROW_GLYPH), 
								&(DefaultFont[Symbol].NarrowGlyph));
			if (EFI_ERROR(Status))
				return EFI_OUT_OF_RESOURCES;

			DefaultFont[Symbol].NarrowGlyph[0] = NGlyph[i];
		}
	}

	for(i = 0; i < Package->NumberOfWideGlyphs; i++)
	{
		Symbol = WGlyph[i].UnicodeWeight;
		if(DefaultFont[Symbol].WideGlyph == NULL)
		{
			Status = pBS->AllocatePool(
								EfiBootServicesData, 
								sizeof(EFI_WIDE_GLYPH), 
								&(DefaultFont[Symbol].WideGlyph));
			if (EFI_ERROR(Status))
				return EFI_OUT_OF_RESOURCES;

			DefaultFont[Symbol].WideGlyph[0] = WGlyph[i];
		}
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DeleteStringsFromDatabase
//
//  Description:
//  This function removes HII strings from private storage and frees allocated memory
//
//  Input:
//  IN DBE_DATABASE *Database - Pointer to private strings storage
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DeleteStringsFromDatabase(DBE_DATABASE *Database)
{
    VOID *FreeLink;
    UINTN *Pointer;
    UINTN i;

    if(Database->RecordCount == 0)
        return;

    Pointer = (UINTN *)(Database->IndexArray);

    for(i = 0; i < Database->RecordCount; i++)
    {
        FreeLink = (VOID *)(UINTN)(*Pointer);
        pBS->FreePool(FreeLink);
        Pointer++;
    }

    MemSet(Database->IndexArray, Database->RecordCount * Database->KeyCount, 0);
    Database->RecordCount = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DeleteSimpleFonts
//
//  Description:
//  This function removes simple fonts from private area and frees allocated memory
//
//  Input:
//  IN EFI_HII_SIMPLE_FONT_PACKAGE_HDR *Package - Pointer to simple font package which fonts
//                                                should be removed
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DeleteSimpleFonts(IN EFI_HII_SIMPLE_FONT_PACKAGE_HDR *Package)
{
	UINT16 i;
	UINT16 Symbol;
	EFI_NARROW_GLYPH *NGlyph;
	EFI_WIDE_GLYPH *WGlyph;

	NGlyph = Package->NarrowGlyphs;
	WGlyph = (EFI_WIDE_GLYPH *)NGlyph;
	(UINT8 *)WGlyph += Package->NumberOfNarrowGlyphs * sizeof(EFI_NARROW_GLYPH);

	for(i = 0; i < Package->NumberOfNarrowGlyphs; i++)
	{
		Symbol = NGlyph[i].UnicodeWeight;
		if(DefaultFont[Symbol].NarrowGlyph != NULL)
        {
			pBS->FreePool(DefaultFont[Symbol].NarrowGlyph);
            DefaultFont[Symbol].NarrowGlyph = NULL;
        }
	}

	for(i = 0; i < Package->NumberOfWideGlyphs; i++)
	{
		Symbol = WGlyph[i].UnicodeWeight;
		if(DefaultFont[Symbol].WideGlyph != NULL)
		{
			pBS->FreePool(DefaultFont[Symbol].WideGlyph);
			DefaultFont[Symbol].WideGlyph = NULL;
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ExportPack
//
//  Description:
//  This function exports the package list with given handle into provided buffer 
//
//  Input:
//  IN EFI_HII_HANDLE Handle - Handle of package list to be exported
//  IN OUT UINTN *BufferSize - Pointer to export buffer size value
//  OUT EFI_HII_PACKAGE_LIST_HEADER *Buffer - Pointer to buffer where to export package lists
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_BUFFER_TOO_SMALL - Export buffer too small
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ExportPack (
    IN EFI_HII_HANDLE                       Handle,
    IN OUT UINTN                            *BufferSize,
    OUT EFI_HII_PACKAGE_LIST_HEADER         *Buffer,
    IN BOOLEAN FirstCall )
{
    EFI_STATUS Status;
    PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *) Handle;
    PACKAGE_LINK *Link;
    UINT32 Size = 0;

	if (Record->Signature != PACKAGE_LIST_RECORD_SIGNATURE) //handle is not valid, return NOT FOUND as SCT requirement
		return EFI_NOT_FOUND;

    if(FirstCall) {
    //on the subsequent call we don't need to update string packages again
        Status = UpdateStringPackages(Handle);
        if(EFI_ERROR(Status))
            return Status;
    }

    Link = (PACKAGE_LINK *)Record->PackageList.pHead;
    while(Link != NULL)
    {
        Size += Link->Package.Length;
        Link = (PACKAGE_LINK *)Link->Link.pNext;
    }

    Size += sizeof(EFI_HII_PACKAGE_LIST_HEADER);

    if(Size > *BufferSize)
    {
        *BufferSize = Size;
        return EFI_BUFFER_TOO_SMALL;
    }

    *BufferSize = Size;
    Buffer->PackageListGuid = Record->Guid;
    Buffer->PackageLength  = Size;
    (UINT8 *)Buffer += sizeof(EFI_HII_PACKAGE_LIST_HEADER);

    Link = (PACKAGE_LINK *)Record->PackageList.pHead;
    while(Link != NULL)
    {
        Size = Link->Package.Length;
        MemCpy(Buffer, &(Link->Package), Size);
        (UINT8 *)Buffer += Size;
        Link = (PACKAGE_LINK *)Link->Link.pNext;
    }

	return EFI_SUCCESS;
}

EFI_STATUS SignalKbLayoutChangedEvent(
    VOID)
{
    EFI_EVENT  Event;
	EFI_GUID   SetKeyboardLayoutEventGuid = EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID;
    EFI_STATUS Status;

	Status = pBS->CreateEventEx(
					EVT_NOTIFY_SIGNAL,
					TPL_CALLBACK,
					SetKbLayoutNotifyFn,
					NULL,
					&SetKeyboardLayoutEventGuid,
					&Event);
    if(EFI_ERROR(Status))
        return Status;

	pBS->SignalEvent(Event);			
	pBS->CloseEvent(Event);

    return EFI_SUCCESS;
}

#pragma warning (default : 4090)

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
