//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/Names.c 7     8/28/09 10:03a Felixp $
//
// $Revision: 7 $
//
// $Date: 8/28/09 10:03a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/Names.c $
// 
// 7     8/28/09 10:03a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 6     7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 5     4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 4     4/10/07 10:04a Felixp
// LookupHID routine renamed to LookupPs2Hid to avoid linking issue when
// linking with FloppyCtrl module
// 
// 3     3/13/06 2:38a Felixp
// 
// 2     3/04/05 1:37p Mandal
// 
// 1     2/01/05 1:11a Felixp
// 
// 3     1/28/05 1:21p Felixp
// bug fix in component name
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     10/28/04 10:19a Olegi
// 
// 2     9/30/04 8:13a Olegi
// HotKeys added.
// 
// 1     9/21/04 5:42p Olegi
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        Names.c
//
// Description: Component name producer for PS/2 Controller DXE driver
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "efi.h"
#include "ps2ctl.h"
#include <Protocol\ComponentName.h>
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#ifndef LANGUAGE_CODE_ENGLISH
#define LANGUAGE_CODE_ENGLISH "eng"
#endif
static BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}
#endif
//----------------------------------------------------------------------

EFI_STATUS PS2GetDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN CHAR8                        *Language,
    OUT CHAR16                      **DriverName
);

EFI_STATUS
PS2GetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN CHAR8                        *Language,
    OUT CHAR16                      **ControllerName
);

extern EFI_DRIVER_BINDING_PROTOCOL gPS2CtlDriverBinding;
extern PS2DEV_TABLE supportedDevices[];

//----------------------------------------------------------------------

CHAR16 *gPS2DriverName = L"AMI PS/2 Driver";

//==================================================================================
// Driver component name instance for PS2Ctl Driver
//==================================================================================
EFI_COMPONENT_NAME_PROTOCOL gPS2CtlDriverName = {
    PS2GetDriverName,
    PS2GetControllerName,
    LANGUAGE_CODE_ENGLISH
};

//----------------------------------------------------------------------


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        PS2GetDriverName
//
// Description: Retrieves a Unicode string that is the user readable name of 
//              the EFI Driver.
//
//
// Parameters:
//   EFI_COMPONENT_NAME_PROTOCOL
//    This       - A pointer to the EFI_COMPONENT_NAME_PROTOCOL instance.
//   CHAR8
//    Language   - A pointer to a three character ISO 639-2 language identifier.
//                 This is the language of the driver name that that the caller
//                 is requesting, and it must match one of the languages specified
//                 in SupportedLanguages.  The number of languages supported by a
//                 driver is up to the driver writer.
//   CHAR16
//    DriverName - A pointer to the Unicode string to return.  This Unicode string
//                 is the name of the driver specified by This in the language
//                 specified by Language.
//
// Output:
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
PS2GetDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN CHAR8                        *Language,
    OUT CHAR16                      **DriverName
)
{
    if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH))
        return EFI_UNSUPPORTED;
    *DriverName = gPS2DriverName;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        PS2GetControllerName
//
// Description: Retrieves a Unicode string that is the user readable name of
//              the controller that is being managed by an EFI Driver.
//
// Parameters:
//   EFI_COMPONENT_NAME_PROTOCOL
//    This             - A pointer to the EFI_COMPONENT_NAME_PROTOCOL instance.
//   EFI_HANDLE
//    ControllerHandle - The handle of a controller that the driver specified by
//                       This is managing.  This handle specifies the controller
//                       whose name is to be returned.
//   EFI_HANDLE
//    ChildHandle      - The handle of the child controller to retrieve the name
//                       of.  This is an optional parameter that may be NULL.  It
//                       will be NULL for device drivers.  It will also be NULL
//                       for a bus drivers that wish to retrieve the name of the
//                       bus controller.  It will not be NULL for a bus driver
//                       that wishes to retrieve the name of a child controller.
//   CHAR8
//    *Language        - A pointer to a three character ISO 639-2 language
//                       identifier.  This is the language of the controller name
//                       that that the caller is requesting, and it must match one
//                       of the languages specified in SupportedLanguages.  The
//                       number of languages supported by a driver is up to the
//                       driver writer.
//   CHAR16
//    **ControllerName - A pointer to the Unicode string to return.  This Unicode
//                       string is the name of the controller specified by
//                       ControllerHandle and ChildHandle in the language
//                       specified by Language from the point of view of the
//                       driver specified by This.
//
// Output:
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
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
PS2GetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN CHAR8                        *Language,
    OUT CHAR16                      **ControllerName
)
{
    ACPI_HID_DEVICE_PATH*   acpiDP;
    PS2DEV_TABLE        *ps2dev = 0;
    if(!Language || !ControllerName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH))
        return EFI_UNSUPPORTED;

    //
    // Find the last device node in the device path and return "Supported" 
    // for mouse and/or keyboard depending on the SDL switches.
    //
    if(!EFI_ERROR(GetPS2_DP(&gPS2CtlDriverBinding, Controller, &acpiDP, EFI_OPEN_PROTOCOL_GET_PROTOCOL)) &&
            LookupPs2Hid(supportedDevices, acpiDP->HID, acpiDP->UID, &ps2dev)){
        *ControllerName = ps2dev->name;
        return EFI_SUCCESS;
    } 
    return EFI_UNSUPPORTED;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
