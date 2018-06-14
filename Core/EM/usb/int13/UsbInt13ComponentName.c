//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbInt13ComponentName.c 1     5/16/08 12:12p Olegi $
//
// $Revision: 1 $
//
// $Date: 5/16/08 12:12p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbInt13ComponentName.c $
// 
// 1     5/16/08 12:12p Olegi
// First check-in.
// 
//**********************************************************************
 
 
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbInt13ComponentName.c
//
// Description:	Component Name Protocol Member Functions for USB Int13.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "Efi.h"
#include "AmiLib.h"
#include <Protocol/ComponentName.h>

EFI_STATUS
UsbInt13CtlDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN CHAR8                        *Language,
    OUT CHAR16                      **DriverName
);

EFI_STATUS
UsbInt13CtlGetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN CHAR8                        *Language,
    OUT CHAR16                      **ControllerName
);


CHAR16 *gUsbInt13DriverName       = L"AMI USB INT13 Driver";
CHAR16 *gUsbInt13ControllerName   = L"USB Mass Storage Legacy Device";


EFI_COMPONENT_NAME_PROTOCOL gUsbInt13ControllerDriverName = {
    UsbInt13CtlDriverName,
    UsbInt13CtlGetControllerName,
    "eng"
};


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbInt13CtlDriverName
//
// Description: Retrieves a Unicode string that is the user readable name of 
//              the EFI Driver.
//
//
// Parameters:
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
UsbInt13CtlDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN CHAR8                        *Language,
    OUT CHAR16                      **DriverName
)
{
    //Supports only "eng" 
    if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
    if (MemCmp(Language, "eng", 3)) return EFI_UNSUPPORTED;
    *DriverName = gUsbInt13DriverName;
    return EFI_SUCCESS;
}



//---------------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Name:        UsbInt13CtlGetControllerName
//
// Description: Retrieves a Unicode string that is the user readable name of
//              the controller that is being managed by an EFI Driver.
//
// Parameters:
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
//<AMI_PHDR_END>
//---------------------------------------------------------------------------
EFI_STATUS
UsbInt13CtlGetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN CHAR8                        *Language,
    OUT CHAR16                      **ControllerName
)
{
    *ControllerName = gUsbInt13ControllerName;
    return EFI_SUCCESS;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
