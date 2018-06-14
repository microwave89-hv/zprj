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
// $Header: /Alaska/BIN/Board/Setup/AmiSetupProtocol.c 3     10/04/12 4:49p Artems $
//
// $Revision: 3 $
//
// $Date: 10/04/12 4:49p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/Setup/AmiSetupProtocol.c $
// 
// 3     10/04/12 4:49p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Added function headers for CHM builder
// [Files]  		AmiSetupProtocol.c
// 
// 2     8/29/12 2:36p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	setup control interactive callback doesn't work
// [RootCause]  	When there are no runtime-registered callbacks,
// build-time callbacks don't present in callback list
// [Solution]  	Fixed code logic to handle situation with no runtime
// callbacks
// [Files]  		AmiSetupProtocol.c Setup.c
// 
// 1     8/28/12 4:10p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Add infrastructure to support runtime registration of
// setup controls callbacks
// [Files]  		Setup.c Setup.h Setup.cif AmiSetupProtocol.c
// AmiSetupProtocol.h
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AmiSetupProtocol.c
//
// Description: AMI Setup protocol implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Setup.h>
#include <Protocol/AmiSetupProtocol.h>

typedef struct {
    DLINK Link;
    SETUP_ITEM_CALLBACK Data;
} AMI_SETUP_CALLBACK_LINK;

static DLIST AmiCallbackList;
extern CALLBACK_PARAMETERS *CallbackParametersPtr;

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    AmiSetupRegisterCallback
//
// Description:
//  This function registers setup control callback
//
// Input:
//  IN UINT16 Class - setup control formset class
//  IN UINT16 SubClass - setup control formset subclass
//  IN UINT16 Key - setup control key
//  IN SETUP_ITEM_CALLBACK_HANDLER *Handler - pointer to callback function
//  OUT EFI_HANDLE *Handle - pointer to store handle of registered callback
//
// Output:
//  EFI_SUCCESS - operation succeeded
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
EFI_STATUS AmiSetupRegisterCallback(
	IN UINT16 Class,
    IN UINT16 SubClass,
    IN UINT16 Key,
    IN SETUP_ITEM_CALLBACK_HANDLER *Handler,
    OUT EFI_HANDLE *Handle
)
{
    EFI_STATUS Status;
    AMI_SETUP_CALLBACK_LINK *NewLink;

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(AMI_SETUP_CALLBACK_LINK), &NewLink);
    if(EFI_ERROR(Status))
        return Status;

    NewLink->Data.Class = Class;
    NewLink->Data.SubClass = SubClass;
    NewLink->Data.Key = Key;
    NewLink->Data.UpdateItem = Handler;

    DListAdd(&AmiCallbackList, (DLINK *)NewLink);
    *Handle = NewLink;
    return EFI_SUCCESS;
}

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    AmiSetupUnRegisterCallback
//
// Description:
//  This function unregisters previously registered callback
//
// Input:
//  IN EFI_HANDLE Handle - handle of callback to unregister
//
// Output:
//  EFI_SUCCESS - operation succeeded
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
EFI_STATUS AmiSetupUnRegisterCallback(
    IN EFI_HANDLE Handle
)
{
    DListDelete(&AmiCallbackList, (DLINK *)Handle);
    pBS->FreePool(Handle);
    return EFI_SUCCESS;
}

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    AmiSetupGetCallbacks
//
// Description:
//  This function returns all registered callbacks
//
// Input:
//  IN OUT UINTN *BufferSize - size of buffer where to store output
//  OUT SETUP_ITEM_CALLBACK *Buffer - buffer to store output
//
// Output:
//  EFI_SUCCESS - operation succeeded
//  EFI_ERROR - operation failed
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
EFI_STATUS AmiSetupGetCallbacks(
	IN OUT UINTN *BufferSize,
    OUT SETUP_ITEM_CALLBACK *Buffer
)
{
    UINTN ActualSize;
    AMI_SETUP_CALLBACK_LINK *Link;

    if(AmiCallbackList.Size == 0)
        return EFI_NOT_FOUND;

    ActualSize = sizeof(SETUP_ITEM_CALLBACK) * AmiCallbackList.Size;
    if(*BufferSize < ActualSize) {
        *BufferSize = ActualSize;
        return EFI_BUFFER_TOO_SMALL;
    }

    if(Buffer == NULL)
        return EFI_INVALID_PARAMETER;

    Link = (AMI_SETUP_CALLBACK_LINK *)AmiCallbackList.pHead;
    while(Link != NULL) {
        Buffer->Class = Link->Data.Class;
        Buffer->SubClass = Link->Data.SubClass;
        Buffer->Key = Link->Data.Key;
        Buffer->UpdateItem = Link->Data.UpdateItem;
        Buffer++;
        Link = (AMI_SETUP_CALLBACK_LINK *)Link->Link.pNext;
    }

    *BufferSize = ActualSize;
    return EFI_SUCCESS;
}

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    AmiSetupGetCallbackParameters
//
// Description:
//  This function returns callback parameters from FormBrowser
//
// Input:
//  OUT CALLBACK_PARAMETERS **Parameters - pointer to store parameters
//
// Output:
//  EFI_SUCCESS - protocol installed
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
EFI_STATUS AmiSetupGetCallbackParameters(
    OUT CALLBACK_PARAMETERS **Parameters
)
{
    *Parameters = CallbackParametersPtr;
    return EFI_SUCCESS;
}

static AMI_SETUP_PROTOCOL AmiSetupProtocol = {
    AmiSetupRegisterCallback,
    AmiSetupUnRegisterCallback,
    AmiSetupGetCallbacks,
    AmiSetupGetCallbackParameters
};

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    InitAmiSetupProtocol
//
// Description:
//  This function installs AMI Setup protocol
//
// Input:
//  None
//
// Output:
//  EFI_SUCCESS - protocol installed
//  EFI_ERROR - error occured during installation
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
EFI_STATUS InitAmiSetupProtocol(
    VOID
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle = NULL;

    DListInit(&AmiCallbackList);
    Status = pBS->InstallMultipleProtocolInterfaces(
		                        &Handle,
		                        &AmiSetupProtocolGuid, 
                                &AmiSetupProtocol,
		                        NULL);
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
