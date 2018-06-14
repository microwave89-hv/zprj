//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IDEBusComponentName.c 17    10/11/10 11:29a Krishnakumarg $
//
// $Revision: 17 $
//
// $Date: 10/11/10 11:29a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IDEBusComponentName.c $
// 
// 17    10/11/10 11:29a Krishnakumarg
// [TAG] - EIP 43249
// [Category] - IMPROVEMENT
// [Severity] - Minor
// [Symptom]  - Non-Ascii character in comments causing build problem in
// japanese XP
// [RootCause]- Presence of Non-Ascii character
// [Solution] -  Remove Non-Ascii character present in the file
// [Files] - IdeSecurity.c,IDESMM.c, InstallIdeSmi, Ata.c, Atapi.c,
// IDEBusComponentName.c, IdeBusMaster.c, IdeHPA.c, IdePowerManagement.c
// 
// 16    8/25/10 4:13a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 15    8/28/09 11:21a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 14    7/01/09 12:24p Rameshr
// Coding Standard and File header updated.
//
// 13    3/04/08 7:51p Felixp
//
// 11    28/02/08 7:01p Anandakrishnanl
// Changed the Protocol member as defined for IdeSecurity.
//
// 10    4/30/07 1:16p Srinin
// Check for valid Child Controller handle added.
//
// 9     4/20/07 6:13p Felixp
//
// 8     13/04/07 3:02p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
// 7     4/10/07 9:05a Felixp
// Bug fix: undeclared identifier
//
// 6     4/05/07 12:54p Srinin
// IdeBusCtlGetControllerName modified to check for valid controller and
// Child  Handles.
//
// 5     3/13/06 2:21a Felixp
//
// 4     1/09/06 11:36a Felixp
//
// 2     12/14/05 3:11p Srinin
// Component name will be returned if either BLOCK_IO or SECURITY
// Protocol is installed on the device.
//
// 1     12/01/05 9:43a Felixp
//
// 7     3/04/05 11:36a Mandal
//
// 6     2/02/05 2:10p Felixp
//
// 5     2/01/05 1:01p Srinin
// Fixed Build errors when library is not used.
//
// 4     1/31/05 11:06a Srinin
// Return proper ComponentName for IDE devices.
//
// 3     1/28/05 1:19p Felixp
// IdeBus is linked together with CORE_DXE
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     12/10/04 1:01p Srinin
// Initial Checkin of IdeBus Driver.
//
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: IDEBusComponentName.c
//
// Description:	Component Name Protocol Member Functions for IDE Bus.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "IdeBus.h"
#include <Protocol\IdeBusBoard.h>

//
//External variables
//

extern EFI_DRIVER_BINDING_PROTOCOL  gIdeBusDriverBinding;
extern PLATFORM_IDE_PROTOCOL        *gPlatformIdeProtocol;
extern EFI_GUID                     gSecurityModeProtocolGuid;
static EFI_GUID                     gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;

extern BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2 );

EFI_STATUS IdeBusCtlDriverName (
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN CHAR8                       *Language,
    OUT CHAR16                     **DriverName );

EFI_STATUS IdeBusCtlGetControllerName (
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN EFI_HANDLE ChildHandle      OPTIONAL,
    IN CHAR8                       *Language,
    OUT CHAR16                     **ControllerName );


CHAR16                      *gIdeBusDriverName     = L"AMI IDE BUS Driver";
CHAR16                      *gIdeBusControllerName = L"PCI IDE Mass Storage Device";


EFI_COMPONENT_NAME_PROTOCOL gIdeBusControllerDriverName = {
    IdeBusCtlDriverName,
    IdeBusCtlGetControllerName,
    LANGUAGE_CODE_ENGLISH
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  IdeBusCtlDriverName
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

EFI_STATUS IdeBusCtlDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN CHAR8                       *Language,
    OUT CHAR16                     **DriverName )
{
    //
    //Supports only English
    //
    if ( !Language || !DriverName ) {
        return EFI_INVALID_PARAMETER;
    }
    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) {
        return EFI_UNSUPPORTED;
    }
    *DriverName = gIdeBusDriverName;
    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
//<AMI_PHDR_START>
//
// FUNCTION:  IdeBusCtlGetControllerName
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
EFI_STATUS IdeBusCtlGetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_HANDLE ChildHandle      OPTIONAL,
    IN CHAR8                       *Language,
    OUT CHAR16                     **ControllerName )
{
    EFI_STATUS                          Status;
    IDE_BUS_PROTOCOL                    *IdeBusInterface;
    EFI_BLOCK_IO_PROTOCOL               *BlkIo;
    SECURITY_PROTOCOL                   *IdeSecurityInterface;
    UINTN                               j, InfoCount;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *pInfo;

    Status = pBS->OpenProtocol( Controller,
                                &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                NULL,
                                gIdeBusDriverBinding.DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    if ( Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED ) {
        return EFI_UNSUPPORTED;
    }

    //
    //Supports only English
    //
    if ( !Language || !ControllerName ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) {
        return EFI_UNSUPPORTED;
    }

    if ( ChildHandle == NULL ) {
        *ControllerName = gIdeBusControllerName;
        return EFI_SUCCESS;
    } else {
        //
        // Make sure the CHILD handle is really a child of controller
        //
        Status = pBS->OpenProtocolInformation(
            Controller,
            &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
            &pInfo, &InfoCount
            );

        if ( EFI_ERROR( Status )) {
            return EFI_UNSUPPORTED;
        }

        for ( j = 0; j < InfoCount; j++ )
        {
            if ( pInfo[j].Attributes != EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER ) {
                continue;
            }

            if ( pInfo[j].ControllerHandle == ChildHandle ) {
                break;
            }
        }

        if ( InfoCount ) {
            pBS->FreePool( pInfo );
        }

        if ( j >= InfoCount ) {
            return EFI_UNSUPPORTED;
        }

        //
        //Open the BLOCK_IO protocol installed on the child device.
        //
        Status = pBS->OpenProtocol( ChildHandle,
                                    &gEfiBlockIoProtocolGuid,
                                    (VOID**)&BlkIo,
                                    gIdeBusDriverBinding.DriverBindingHandle,
                                    Controller,
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL );

        if ( EFI_ERROR( Status )) {
            //
            //If BLKIO protocol is not installed, maybe Securitymode protocol is installed.
            //
            Status = pBS->OpenProtocol( ChildHandle,
                                        &gSecurityModeProtocolGuid,
                                        (VOID**)&IdeSecurityInterface,
                                        gIdeBusDriverBinding.DriverBindingHandle,
                                        Controller,
                                        EFI_OPEN_PROTOCOL_GET_PROTOCOL );

            //
            //Return Error.
            //
            if ( EFI_ERROR( Status )) {
                return EFI_UNSUPPORTED;
            }

            IdeBusInterface = IdeSecurityInterface->BusInterface;
        }
        else {
            IdeBusInterface = ((IDE_BLOCK_IO*)BlkIo)->IdeBusInterface;
        }

        if ( IdeBusInterface->IdeDeviceHandle != ChildHandle ) {
            return EFI_UNSUPPORTED;
        }

        *ControllerName = IdeBusInterface->IdeDevice.UDeviceName->UnicodeString;
        return EFI_SUCCESS;
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
