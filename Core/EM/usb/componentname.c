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

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/componentname.c 12    1/11/13 4:19a Ryanchou $
//
// $Revision: 12 $
//
// $Date: 1/11/13 4:19a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/componentname.c $
// 
// 12    1/11/13 4:19a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 11    10/24/11 8:22a Wilsonlee
// [TAG]  		EIP69250
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB driver doesn't pass SCT 2.3 ComponentName2 protocol.
// [RootCause]  	There is no checking if passed controller handle is NULL
// in AMIUSBComponentNameGetControllerName function.
// [Solution]  	Check controller handle is NULL in
// AMIUSBComponentNameGetControllerName function.
// [Files]  		componentname.c efiusbccid.c efiusbhid.c
// 
// 10    5/03/11 10:48a Ryanchou
// [TAG]  		EIP59272
// [Category]  	Improvement
// [Description]  	According Uefi 2.1 Aptio porting document, changes made
// to install the component name protocol.
// [Files]  		componentname.c, componentname.h, efiusbkb.c, efiusbmass.c,
// efiusbms.c, uhcd.c, uhcd.h, usbbus.c
// 
// 9     3/04/11 1:31p Olegi
// 
// 8     3/04/11 1:25p Olegi
// [TAG]  		EIP55172
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Install EFI_COMPONENT_NAME_PROTOCOL if BIOS is in UEFI
// 2.0 mode and EFI_COMPONENT_NAME2_PROTOCOL if BIOS is in UEFI 2.1 mode.
// [Files]  		uhcd.c
// usbbus.c
// efiusbkb.c
// efiusbmass.c
// efiusbms.c
// componentname.c
// componentname.h
// 
// 7     5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 6     3/20/07 1:29p Olegi
//
// 4     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 3     5/19/05 8:06p Olegi
// Aptio changes in driver 8.1 implementation.
//
// 2     5/10/05 4:13p Andriyn
// USBBUS implementation
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           ComponentName.c
//
//  Description:    AMI USB Component Name definitions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#include "Efi.h"
#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"
#include "componentname.h"
#include <Protocol\ComponentName.h>

                                        //(EIP59272)>
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
EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#endif
                                        
static NAME_SERVICE_T cn_template = {
  AMIUSBComponentNameGetDriverName,
  AMIUSBComponentNameGetControllerName,
  LANGUAGE_CODE_ENGLISH
};
                                        //<(EIP59272)


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitNamesStatic
//
// Description: USB device and controller names initializer.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_COMPONENT_NAME_PROTOCOL*
InitNamesStatic(
    NAME_SERVICE_T* NameService,
    CHAR16* Driver,
    CHAR16* Component
)
{
    *NameService  = cn_template;
    NameService->driver_name = Driver;
    NameService->component_static = Component;
    NameService->component_cb = 0;
    return &NameService->icn;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitNamesProtocol
//
// Description: Component names protocol initializer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_COMPONENT_NAME_PROTOCOL*
InitNamesProtocol(
    NAME_SERVICE_T* NameService,
    CHAR16* Driver,
    COMPONENT_CB_T ComponentCb
)
{
    *NameService  = cn_template;
    NameService->driver_name = Driver;
    NameService->component_static = 0;
    NameService->component_cb = ComponentCb;
    return &NameService->icn;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AMIUSBComponentNameGetDriverName
//
// Description: Retrieves a Unicode string that is the user readable name of
//              the EFI Driver.
//
//
// Input:
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
AMIUSBComponentNameGetDriverName (
  EFI_COMPONENT_NAME_PROTOCOL  *ComponentNameProtocol,
  CHAR8                        *Language,
  CHAR16                       **DriverName
  )
{
    
    NAME_SERVICE_T* This = (NAME_SERVICE_T*)ComponentNameProtocol;
                                        //(EIP59272)>
    if(!Language || !DriverName) {
        return EFI_INVALID_PARAMETER;
    }
    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) {
        return EFI_UNSUPPORTED;
    }
                                        //<(EIP59272)
    *DriverName = This->driver_name;
    return  EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AMIUSBComponentNameGetControllerName
//
// Description: Retrieves a Unicode string that is the user readable name of
//              the controller that is being managed by an EFI Driver.
//
// Input:
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
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AMIUSBComponentNameGetControllerName (
  EFI_COMPONENT_NAME_PROTOCOL  *ComponentNameProtocol,
  EFI_HANDLE                   Controller,
  EFI_HANDLE                   Child,
  CHAR8                        *Language,
  CHAR16                       **ControllerName
  )
{
    NAME_SERVICE_T* This = (NAME_SERVICE_T*)ComponentNameProtocol;
                                        //(EIP59272)>
    if(!Language || !ControllerName || !Controller) {	//(EIP69250)
        return EFI_INVALID_PARAMETER;
    }
    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) {
        return EFI_UNSUPPORTED;
    }
                                        //<(EIP59272)
    if( This->component_cb != 0){
        CHAR16 *Str = This->component_cb(Controller, Child);
        if(Str==0) return EFI_UNSUPPORTED;
        *ControllerName = Str;
    } else {
        if (Child != NULL) {
            return EFI_UNSUPPORTED;
        }
        *ControllerName = This->component_static;
    }

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
