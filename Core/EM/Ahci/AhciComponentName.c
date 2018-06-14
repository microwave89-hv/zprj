//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciComponentName.c 7     1/27/14 4:57a Rameshr $
//
// $Revision: 7 $
//
// $Date: 1/27/14 4:57a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciComponentName.c $
// 
// 7     1/27/14 4:57a Rameshr
// [TAG]  		EIP148180
// [Category]  	Improvement
// [Description]  	Change from EFI_MBR_WRITE_PROTECTION_PROTOCOL to
// AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL
// [Files]  		Ahcibus.c, Ahcibus.h, AhciComponentName.c, AhciController.c
// 
// 6     2/10/11 10:35a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSrc.mak
// AhciBus.c
// AhciController.c
// AhciComponentName.c
// AhciBus.h
// AhciController.h
// 
// 5     5/07/10 11:45a Krishnakumarg
// Coding standard update
// 
// 4     3/26/10 5:37p Krishnakumarg
// UEFI2.1 compliance change EIP#34744.
// 
// 3     4/28/09 3:57p Rameshr
// 
// HDD password support in RAID mode
// EIP:20421
// 
// 2     5/28/08 9:39a Rameshraju
// 
// 1     28/02/08 6:03p Anandakrishnanl
// AHCI Bus Driver initial check-in.
// 
// 
// 
//**********************************************************************

#include "AhciBus.h"

extern  EFI_GUID gSecurityModeProtocolGuid;
static EFI_GUID gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;
extern  EFI_DRIVER_BINDING_PROTOCOL gAhciBusDriverBinding;

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#define LANGUAGE_CODE_ENGLISH "eng"
#define EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME_PROTOCOL
#endif

EFI_STATUS AhciBusCtlDriverName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN CHAR8                        *Language,
    OUT CHAR16                      **DriverName
);

EFI_STATUS
AhciBusCtlGetControllerName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN CHAR8                        *Language,
    OUT CHAR16                      **ControllerName
);


CHAR16 *gAhciBusDriverName = L"AMI AHCI BUS Driver";
CHAR16 *gAhciBusControllerName = L"AHCI Mass Storage Controller";

//==================================================================================
EFI_COMPONENT_NAME2_PROTOCOL gAhciBusControllerDriverName = {
    AhciBusCtlDriverName,
    AhciBusCtlGetControllerName,
    LANGUAGE_CODE_ENGLISH
};

static BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  AhciBusCtlDriverName
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
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AhciBusCtlDriverName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN CHAR8                        *Language,
    OUT CHAR16                      **DriverName
)
{
    //
    //Supports only English
    //
    if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) return EFI_UNSUPPORTED;
    *DriverName = gAhciBusDriverName;
    return EFI_SUCCESS;
}



//---------------------------------------------------------------------------
//<AMI_PHDR_START>
//
// FUNCTION:  AhciBusCtlGetControllerName
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
//---------------------------------------------------------------------------


EFI_STATUS
AhciBusCtlGetControllerName(
    IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN CHAR8                        *Language,
    OUT CHAR16                      **ControllerName
)
{

    EFI_STATUS                      Status;
    SATA_DEVICE_INTERFACE           *SataDevInterface;
    EFI_BLOCK_IO_PROTOCOL           *BlkIo;
    SECURITY_PROTOCOL               *AhciSecurityInterface;
    UINTN                           j, InfoCount;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *pInfo;

        Status = pBS->OpenProtocol( Controller,
                                &gEfiIdeControllerInitProtocolGuid,
                                NULL,
                                gAhciBusDriverBinding.DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

        if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) {
            return EFI_UNSUPPORTED;
        }

    //
    //Supports only "eng" 
    //
    if(!Language || !ControllerName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) return EFI_UNSUPPORTED;

    if (ChildHandle == NULL) {
        *ControllerName = gAhciBusControllerName;
        return EFI_SUCCESS;
    }
    else {
        Status = pBS->OpenProtocolInformation(
            Controller,
            &gEfiIdeControllerInitProtocolGuid,
            &pInfo,&InfoCount
        );
        if (EFI_ERROR(Status))  return EFI_UNSUPPORTED;
        for(j=0; j<InfoCount; j++) {
            if (pInfo[j].Attributes!=EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) continue;
            if (pInfo[j].ControllerHandle==ChildHandle) break;
        }
        if (InfoCount) pBS->FreePool(pInfo);
        if (j >= InfoCount) return EFI_UNSUPPORTED; 

        //
        // Open the BLOCK_IO protocol installed on the child device.
        //
        Status = pBS->OpenProtocol ( ChildHandle,   
                                    &gEfiBlockIoProtocolGuid,  
                                    (VOID **)&BlkIo,
                                    gAhciBusDriverBinding.DriverBindingHandle,   
                                    Controller,   
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);


        if (EFI_ERROR(Status)) {
            //
            // If BLKIO protocol is not installed, maybe Securitymode
            // protocol is installed.
            //
            Status = pBS->OpenProtocol ( ChildHandle,
                                    &gSecurityModeProtocolGuid,
                                    (VOID **)&AhciSecurityInterface,
                                    gAhciBusDriverBinding.DriverBindingHandle,
                                    Controller,
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);

            //
            // Return Error.
            //
            if (EFI_ERROR(Status)) {
                return EFI_UNSUPPORTED;
            }    
            SataDevInterface = AhciSecurityInterface->BusInterface;
        }else {
            SataDevInterface = ((SATA_BLOCK_IO *)BlkIo)->SataDevInterface;
        }
        if (SataDevInterface->IdeDeviceHandle != ChildHandle) return EFI_UNSUPPORTED;

        *ControllerName = SataDevInterface->UDeviceName->UnicodeString;
        return EFI_SUCCESS;
    }

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
