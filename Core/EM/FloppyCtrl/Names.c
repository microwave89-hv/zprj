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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/Names.c 10    8/28/09 10:29a Felixp $
//
// $Revision: 10 $
//
// $Date: 8/28/09 10:29a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/Names.c $
// 
// 10    8/28/09 10:29a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 9     7/02/09 12:54p Yul
// Syns to coding standards
//
// 8     7/02/09 10:14a Yul
// Update Header and Tailer and syns with coding standards
//
// 7     4/13/07 1:38p Ambikas
// Coding standards changes: changed spaces, dashes, etc.
//
// 6     4/13/07 11:59a Ambikas
//
// 5     4/13/07 11:53a Ambikas
// Coding standard changes: updated the year in the AMI copyright header
// and footer; removed commented out _asm jmp $.
//
// 4     4/10/07 10:01a Felixp
// LookupHID routine renamed to LookupFloppyHid to avoid linking issue
// when linking with PS2CTRL module
//
// 3     3/13/06 2:22a Felixp
//
// 2     3/04/05 11:31a Mandal
//
//**********************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: Names.c
//
// Description:	Definitions for EFI_COMPONENT_NAME_PROTOCOL
// (GetDriverName, GetControllerName) for FloppyCtrl driver.
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>


//----------------------------------------------------------------------

#include "FloppyCtrl.h"

//----------------------------------------------------------------------

EFI_STATUS FloppyGetDriverName (
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN CHAR8                       *Language,
    OUT CHAR16                     **DriverName );

EFI_STATUS FloppyGetControllerName (
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN EFI_HANDLE ChildHandle      OPTIONAL,
    IN CHAR8                       *Language,
    OUT CHAR16                     **ControllerName );

extern EFI_DRIVER_BINDING_PROTOCOL gFloppyCtrlDriverBindingProtocol;

CHAR16 *gFloppyDriverName = L"AMI Floppy Driver";
CHAR16 *gFloppyCtrlName   = L"Floppy Controller";

//==========================================================================
// Driver component name instance for FloppyCtl Driver
//==========================================================================
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
EFI_COMPONENT_NAME_PROTOCOL        gFloppyCtlDriverName = {
    FloppyGetDriverName,
    FloppyGetControllerName,
    LANGUAGE_CODE_ENGLISH
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  FloppyGetDriverName
//
// DESCRIPTION: Retrieves a Unicode string that is the user readable name of
//              the EFI Driver.
//
//
// Input:
//    This       - A pointer to the EFI_COMPONENT_NAME_PROTOCOL instance.
//    Language   - Pointer to a three character ISO 639-2 language identifier
//                 This is language of the driver name that that the caller
//                 is requesting, must match one of the languages specified
//                 in SupportedLanguages. Number of languages supported by a
//                 driver is up to the driver writer.
//    DriverName - A pointer to the Unicode string to return. Unicode string
//                 is the name of the driver specified by This in the
//                 language specified by Language.
//
// Output:
//    EFI_SUCCES            - Unicode string for the Driver specified by This
//                            and the language specified by Language was
//                             returned in DriverName.
//    EFI_INVALID_PARAMETER - Language is NULL.
//    EFI_INVALID_PARAMETER - DriverName is NULL.
//    EFI_UNSUPPORTED       - The driver specified by This does not support
//                            language specified by Language.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FloppyGetDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN CHAR8                       *Language,
    OUT CHAR16                     **DriverName )
{
    if ( !Language || !DriverName ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) {
        return EFI_UNSUPPORTED;
    }
    *DriverName = gFloppyDriverName;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  FloppyGetControllerName
//
// DESCRIPTION: Retrieves a Unicode string that is the user readable name of
//              the controller that is being managed by an EFI Driver.
//
// Input:
//	IN EFI_COMPONENT_NAME_PROTOCOL  *This,
//	IN EFI_HANDLE                   Controller,
//	IN EFI_HANDLE                   ChildHandle        OPTIONAL,
//	IN CHAR8                        *Language,
//
// Output:
//    OUT CHAR16            **ControllerName
//    A pointer to the Unicode string to return.  This Unicode
//    string is the name of the controller specified by
//    ControllerHandle and ChildHandle in the language
//    specified by Language from the point of view of the
//    driver specified by This.
//    EFI_SUCCESS           - Unicode string for the user readable name in
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
//    EFI_UNSUPPORTED       - The driver specified by This does not support
//                            the language specified by Language.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FloppyGetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_HANDLE ChildHandle      OPTIONAL,
    IN CHAR8                       *Language,
    OUT CHAR16                     **ControllerName )
{
    ACPI_HID_DEVICE_PATH * acpiDP;

    if ( !Language || !ControllerName ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) {
        return EFI_UNSUPPORTED;
    }

    //
    // Find the last device node in the device path and return "Supported"
    // for mouse and/or keyboard depending on the SDL switches.
    //
    if ( !EFI_ERROR( GetFloppy_DP( &gFloppyCtrlDriverBindingProtocol, \
                                   Controller, &acpiDP, EFI_OPEN_PROTOCOL_GET_PROTOCOL, FALSE ))
         && LookupFloppyHid( acpiDP->HID, acpiDP->UID )) {
        *ControllerName = gFloppyCtrlName;
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
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
