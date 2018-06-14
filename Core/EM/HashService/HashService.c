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
// $Header: /Alaska/SOURCE/Core/Modules/HashService/HashService.c 2     8/28/12 4:28p Artems $
//
// $Revision: 2 $
//
// $Date: 8/28/12 4:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/HashService/HashService.c $
// 
// 2     8/28/12 4:28p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Implementation of hash protocol
// [Files]  		HasService.c HashService.sdl
// 
// 1     5/24/12 3:33p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Added HashService protocol infrastructure
// [Files]  		HashService.cif
// HashService.sdl
// HashService.mak
// HashService.c
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: HashService.c
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Protocol\Hash.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\ServiceBinding.h>
#include <Protocol\AmiDigitalSignature.h>


/* Dummy DriverBinding protocol */
EFI_STATUS	HashServiceDriverBindingSupported ( 
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath)
{ return EFI_UNSUPPORTED; }

EFI_STATUS	HashServiceDriverBindingStart ( 
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath)
{ return EFI_UNSUPPORTED; }

EFI_STATUS	HashServiceDriverBindingStop ( 
	IN EFI_DRIVER_BINDING_PROTOCOL	*This,
	IN EFI_HANDLE			        ControllerHandle,
	IN  UINTN			            NumberOfChildren,
	IN  EFI_HANDLE			        *ChildHandleBuffer)
{ return EFI_UNSUPPORTED; }

EFI_DRIVER_BINDING_PROTOCOL HashServiceDriverBindingProtocol = {
	HashServiceDriverBindingSupported,
	HashServiceDriverBindingStart,
	HashServiceDriverBindingStop,
	0x10,
	NULL,
	NULL
};

static EFI_GUID AmiDigitalSignatureProtocolGuid = AMI_DIGITAL_SIGNATURE_PROTOCOL_GUID;
static AMI_DIGITAL_SIGNATURE_PROTOCOL *AmiDigitalSignatureProtocol = NULL;
static DLIST HashChildList;

typedef struct {
    DLINK Link;
    EFI_HANDLE Handle;
    EFI_HASH_PROTOCOL Protocol;
} HASH_CHILD_LINK;

/* Hash service binding protocol */
EFI_STATUS HashServiceCreateChild (
    IN EFI_SERVICE_BINDING_PROTOCOL *This,
    IN OUT EFI_HANDLE *ChildHandle
);

EFI_STATUS HashServiceDestroyChild (
    IN EFI_SERVICE_BINDING_PROTOCOL*This,
    IN EFI_HANDLE ChildHandle
);

EFI_SERVICE_BINDING_PROTOCOL HashServiceBindingProtocol = {
    HashServiceCreateChild,
    HashServiceDestroyChild
};

EFI_STATUS HsGetHashSize(
    IN  CONST EFI_HASH_PROTOCOL     *This,
    IN  CONST EFI_GUID              *HashAlgorithm,
    OUT UINTN                       *HashSize
) 
{
    if(HashSize == NULL || This == NULL || HashAlgorithm == NULL)
        return EFI_INVALID_PARAMETER;

    if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha1Guid)) {
        *HashSize = SHA1_DIGEST_SIZE;
    } else if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha256Guid)) {
        *HashSize = SHA256_DIGEST_SIZE;
    } else {
        return EFI_UNSUPPORTED;
    }

    return EFI_SUCCESS; 
}

EFI_STATUS HsHash(
    IN CONST EFI_HASH_PROTOCOL      *This,
    IN CONST EFI_GUID               *HashAlgorithm,
    IN BOOLEAN                      Extend,
    IN CONST UINT8                  *Message,
    IN UINT64                       MessageSize,
    IN OUT EFI_HASH_OUTPUT          *Hash
) 
{
    UINTN Count;
    UINTN Size[2];
    UINT8 *Chunks[2];
    UINTN HashSize;
    EFI_STATUS Status;
    UINT8 *Buffer;

    if(Message == NULL || Hash == NULL || This == NULL || HashAlgorithm == NULL)
        return EFI_INVALID_PARAMETER;

    if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha1Guid)) {
        Buffer = *(Hash->Sha1Hash);
        HashSize = SHA1_DIGEST_SIZE;
    } else if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha256Guid)) {
        Buffer = *(Hash->Sha256Hash);
        HashSize = SHA256_DIGEST_SIZE;
    } else {
        return EFI_UNSUPPORTED;
    }

    if(Extend) {
/*
        Count = 2;
        Size[0] = (UINTN)MessageSize;
        Chunks[0] = (UINT8*)Message;
*/
        return EFI_UNSUPPORTED;
    } else {
        Count = 1;
        Size[0] = (UINTN)MessageSize;
        Chunks[0] = (UINT8*)Message;
    }

    Status = AmiDigitalSignatureProtocol->Hash(AmiDigitalSignatureProtocol,
                                               HashAlgorithm,
                                               Count,
                                               Chunks,
                                               Size,
                                               Buffer);
        
    return Status; 
}


EFI_STATUS HashServiceEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle = NULL;

    InitAmiLib(ImageHandle,SystemTable);

    Status = pBS->LocateProtocol(&AmiDigitalSignatureProtocolGuid, NULL, &AmiDigitalSignatureProtocol);
    if(EFI_ERROR(Status))
        return Status;

    DListInit(&HashChildList);

    HashServiceDriverBindingProtocol.ImageHandle = ImageHandle;
    HashServiceDriverBindingProtocol.DriverBindingHandle = NULL;

    Status = pBS->InstallMultipleProtocolInterfaces(
                                &HashServiceDriverBindingProtocol.DriverBindingHandle,
                                &gEfiDriverBindingProtocolGuid, 
                                &HashServiceDriverBindingProtocol,
                                &gEfiHashServiceBindingProtocolGuid,
                                &HashServiceBindingProtocol,
                                NULL);


    return Status;
}

EFI_STATUS HashServiceCreateChild (
    IN EFI_SERVICE_BINDING_PROTOCOL *This,
    IN OUT EFI_HANDLE *ChildHandle
)
{
    EFI_STATUS Status;
    HASH_CHILD_LINK *NewLink;

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(HASH_CHILD_LINK), &NewLink);
    if(EFI_ERROR(Status))
        return Status;

    NewLink->Handle = *ChildHandle;
    NewLink->Protocol.GetHashSize = HsGetHashSize;
    NewLink->Protocol.Hash = HsHash;

    DListAdd(&HashChildList, (DLINK *)NewLink);

    Status = pBS->InstallMultipleProtocolInterfaces(&(NewLink->Handle), &gEfiHashProtocolGuid, &(NewLink->Protocol), NULL);
    if(!EFI_ERROR(Status) && *ChildHandle == NULL)
        *ChildHandle = NewLink->Handle;

    return Status;
}

EFI_STATUS HashServiceDestroyChild (
    IN EFI_SERVICE_BINDING_PROTOCOL*This,
    IN EFI_HANDLE ChildHandle
)
{
    EFI_STATUS Status;
    EFI_HASH_PROTOCOL *Instance;
    VOID *Start;
    
    Status = pBS->HandleProtocol(ChildHandle, &gEfiHashProtocolGuid, &Instance);
    if(EFI_ERROR(Status))
        return Status;

    Status = pBS->UninstallMultipleProtocolInterfaces(ChildHandle, &gEfiHashProtocolGuid, Instance);
    if(!EFI_ERROR(Status)) {
        Start = OUTTER(Instance, Protocol, HASH_CHILD_LINK);
        DListDelete(&HashChildList, (DLINK *)Start);
        pBS->FreePool(Start);
    }

    return Status;
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