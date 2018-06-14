//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeComponentName.c 2     9/04/14 7:36a Anandakrishnanl $
//
// $Revision: 2 $
//
// $Date: 9/04/14 7:36a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeComponentName.c $
// 
// 2     9/04/14 7:36a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		
// Nvme.cif	
// Nvme.mak	
// Nvme.uni
// Nvme.chm	
// NvmeSetup.c
// NvmeBus.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// [NvmeControllerLib]
// [NvmeSmm]
// [NVMEINT13]
// [NvmeProtocol]
// 
// 1     6/20/14 6:27a Anandakrishnanl
// [TAG]  		EIP172958
// [Category]  	New Feature
// [Description]  	Nvme Driver Intial Checkin
// [Files]  		Nvme.cif
// Nvme.sdl
// Nvme.mak
// Nvme.sd
// Nvme.uni
// Nvme.chm
// NvmeSetup.c
// NvmeBus.c
// NvmeController.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// NvmeController.h
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmeComonentName.c
//
// Description: Provides Controller and device Name information 
//
//<AMI_FHDR_END>
//**********************************************************************

#include "NvmeIncludes.h"
#include "NvmeBus.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>

extern  EFI_DRIVER_BINDING_PROTOCOL gNvmeBusDriverBinding;
static EFI_GUID gAmiNvmeControllerProtocolGuid = AMI_NVME_CONTROLLER_PROTOCOL_GUID;

EFI_STATUS 
NvmeBusCtlDriverName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN CHAR8                         *Language,
    OUT CHAR16                       **DriverName
);

EFI_STATUS
NvmeBusCtlGetControllerName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN EFI_HANDLE                    ControllerHandle,
    IN EFI_HANDLE                    ChildHandle        OPTIONAL,
    IN CHAR8                         *Language,
    OUT CHAR16                       **ControllerName
);


CHAR16 *gNvmeBusDriverName = L"AMI NVMe BUS Driver";
CHAR16 *gNvmeBusControllerName = L"NVMe Mass Storage Controller";

//==================================================================================
EFI_COMPONENT_NAME2_PROTOCOL gNvmeBusControllerDriverName = {
    NvmeBusCtlDriverName,
    NvmeBusCtlGetControllerName,
    LANGUAGE_CODE_ENGLISH
};

//**********************************************************************
//<AMI_PHDR_START>
//
// FUNCTION:  NvmeBusCtlDriverName
//
// DESCRIPTION: Retrieves a Unicode string that is the user readable name of 
//              the EFI Driver.
//
//
// PARAMETERS:
//    This       - A pointer to the EFI_COMPONENT_NAME_PROTOCOL instance.
//    Language   - A pointer to a three character ISO 639-2 language identifier.
//                 This is the language of the driver name that that the caller
//                 is requesting, and it must match one of the languages specified
//                 in SupportedLanguages.  The number of languages supported by a
//                 driver is up to the driver writer.
//    DriverName - A pointer to the Unicode string to return.  This Unicode string
//                 is the name of the driver specified by This in the language
//                 specified by Language.
//
// RETURN:
//    EFI_SUCCES            - The Unicode string for the Driver specified by This
//                            and the language specified by Language was returned
//                            in DriverName.
//    EFI_INVALID_PARAMETER - Language is NULL.
//    EFI_INVALID_PARAMETER - DriverName is NULL.
//    EFI_UNSUPPORTED       - The driver specified by This does not support the
//                            language specified by Language.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
NvmeBusCtlDriverName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN CHAR8                         *Language,
    OUT CHAR16                       **DriverName
)
{
    //
    //Supports only English
    //
    if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
    if (Strcmp( Language, LANGUAGE_CODE_ENGLISH)) return EFI_UNSUPPORTED;
    *DriverName = gNvmeBusDriverName;
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// FUNCTION:  NvmeBusCtlGetControllerName
//
// DESCRIPTION: Retrieves a Unicode string that is the user readable name of
//              the controller that is being managed by an EFI Driver.
//
// PARAMETERS:
//    This             - A pointer to the EFI_COMPONENT_NAME_PROTOCOL instance.
//    ControllerHandle - The handle of a controller that the driver specified by
//                       This is managing.  This handle specifies the controller
//                       whose name is to be returned.
//    ChildHandle      - The handle of the child controller to retrieve the name
//                       of.  This is an optional parameter that may be NULL.  It
//                       will be NULL for device drivers.  It will also be NULL
//                       for a bus drivers that wish to retrieve the name of the
//                       bus controller.  It will not be NULL for a bus driver
//                       that wishes to retrieve the name of a child controller.
//    Language         - A pointer to a three character ISO 639-2 language
//                       identifier.  This is the language of the controller name
//                       that that the caller is requesting, and it must match one
//                       of the languages specified in SupportedLanguages.  The
//                       number of languages supported by a driver is up to the
//                       driver writer.
//    ControllerName   - A pointer to the Unicode string to return.  This Unicode
//                       string is the name of the controller specified by
//                       ControllerHandle and ChildHandle in the language
//                       specified by Language from the point of view of the
//                       driver specified by This.
//
// RETURNS:
//    EFI_SUCCESS           - The Unicode string for the user readable name in the
//                            language specified by Language for the driver
//                            specified by This was returned in DriverName.
//    EFI_INVALID_PARAMETER - ControllerHandle is not a valid EFI_HANDLE.
//    EFI_INVALID_PARAMETER - ChildHandle is not NULL and it is not a valid
//                            EFI_HANDLE.
//    EFI_INVALID_PARAMETER - Language is NULL.
//    EFI_INVALID_PARAMETER - ControllerName is NULL.
//    EFI_UNSUPPORTED       - The driver specified by This is not currently
//                            managing the controller specified by
//                            ControllerHandle and ChildHandle.
//    EFI_UNSUPPORTED       - The driver specified by This does not support the
//                            language specified by Language.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
NvmeBusCtlGetControllerName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN EFI_HANDLE                    Controller,
    IN EFI_HANDLE                    ChildHandle        OPTIONAL,
    IN CHAR8                         *Language,
    OUT CHAR16                       **ControllerName
)
{

    EFI_STATUS                      Status;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController;
    ACTIVE_NAMESPACE_DATA           *ActiveNameSpace;
    EFI_LIST_ENTRY                      *LinkData;

    // Check if gAmiNvmeControllerProtocolGuid is installed on the device
    Status = pBS->OpenProtocol( Controller,
                    &gAmiNvmeControllerProtocolGuid,
                    (VOID **)&NvmeController,
                    gNvmeBusDriverBinding.DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    
    if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) {
        return EFI_UNSUPPORTED;
    }

    //
    //Supports only "en-US" 
    //
    if(!Language || !ControllerName || !Controller) return EFI_INVALID_PARAMETER;
    if (Strcmp( Language, LANGUAGE_CODE_ENGLISH)) return EFI_UNSUPPORTED;

    if (ChildHandle == NULL) {
        *ControllerName = gNvmeBusControllerName;
        return EFI_SUCCESS;
    } else {
        
          for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; \
              LinkData != &NvmeController->ActiveNameSpaceList; 
              LinkData = LinkData->ForwardLink) {
            
              ActiveNameSpace = _CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);

              if (ActiveNameSpace->NvmeDeviceHandle == ChildHandle){
                  *ControllerName = ActiveNameSpace->UDeviceName->UnicodeString;
                  return EFI_SUCCESS;
                
              }
          }
    }
    
    return EFI_UNSUPPORTED;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
