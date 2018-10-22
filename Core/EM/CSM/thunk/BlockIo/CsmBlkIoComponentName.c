//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmBlkIoComponentName.c 7     9/09/15 11:42a Olegi $
//
// $Revision: 7 $
//
// $Date: 9/09/15 11:42a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmBlkIoComponentName.c $
// 
// 7     9/09/15 11:42a Olegi
// cleanup
// 
// 6     12/23/13 3:38p Olegi
// EIP128504: implement EFI_COMPONENT2_NAME_PROTOCOL for CsmBlockIo driver
// 
// 5     1/12/10 11:50a Olegi
// Copyright message updated.
// 
// 4     10/03/07 4:41p Yakovlevs
// Removed Component Name Protocol and its Strings in NO DEBUG mode to
// save some space. 
// 
// 3     4/27/07 5:14p Olegi
// CSM.CHM file preparation.
// 
// 2     3/04/05 1:43p Mandal
// 
// 1     2/15/05 10:59a Olegi
// Initial VSS check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        CsmBlkIoComponentName.c
//
// Description: Set of functions that implement Component Name protocol
//              for the CSM BlockIO driver.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "CsmBlockIo.h"

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#define LANGUAGE_CODE_ENGLISH "eng"
#define EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME_PROTOCOL
#endif

//
// EFI Component Name Functions
//
EFI_STATUS
CsmBlockIoComponentNameGetDriverName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName
    );

EFI_STATUS
CsmBlockIoComponentNameGetControllerName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN  EFI_HANDLE                   ControllerHandle,
    IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **ControllerName
    );

CHAR16 *gCsmBlockIoDriverName = L"AMI CSM Block I/O Driver";
CHAR16 gCsmBlockIoControllerName[256];

EFI_COMPONENT_NAME2_PROTOCOL gCsmBlockIoComponentName = {
  CsmBlockIoComponentNameGetDriverName,
  CsmBlockIoComponentNameGetControllerName,
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
// FUNCTION:  CsmBlockIoComponentNameGetDriverName
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
CsmBlockIoComponentNameGetDriverName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName
    )
{
    //
    //Supports only English
    //
    if (!Language || !DriverName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) return EFI_UNSUPPORTED;
	*DriverName = gCsmBlockIoDriverName;
	return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
//<AMI_PHDR_START>
//
// FUNCTION:  CsmBlockIoComponentNameGetControllerName
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
CsmBlockIoComponentNameGetControllerName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN  EFI_HANDLE                   ControllerHandle,
    IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **ControllerName
    )
{
    EFI_STATUS                      Status;
    EFI_LEGACY_BIOS_EXT_PROTOCOL    *LegacyBiosExt;
    UINT8                           BbsCount;
    BBS_TABLE                       *BbsEntry;
    UINT32                          i;
    EFI_HANDLE                      Handle;
    CHAR8                           *Str;
    UINT8                           Index = 0;

    //
    //Supports only "eng" 
    //
    if (!Language || !ControllerName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) return EFI_UNSUPPORTED;
    if (ChildHandle == NULL) return EFI_UNSUPPORTED;

    Status = pBS->LocateProtocol(&gEfiLegacyBiosExtProtocolGuid, NULL, (VOID**)&LegacyBiosExt);
    if (EFI_ERROR(Status)) return Status;

    Status = LegacyBiosExt->GetBbsTable(&BbsEntry, &BbsCount);
    if (EFI_ERROR(Status)) return Status;

    pBS->SetMem(gCsmBlockIoControllerName, sizeof(gCsmBlockIoControllerName), 0);

    for (i = 0; i < MAX_BBS_ENTRIES_NO; i++, BbsEntry++) {
        Handle = *(VOID**)(&BbsEntry->IBV1);
        if (Handle == ChildHandle) {
            Str = (CHAR8*)(UINTN)((BbsEntry->DescStringSegment<<4) + BbsEntry->DescStringOffset);
            if (Str == NULL) return EFI_UNSUPPORTED;
            //
            // Transfer Ascii code to Unicode
            //
            while (Str[Index] != 0) {
                gCsmBlockIoControllerName[Index] = (CHAR16)Str[Index];
                Index++;
            }

            *ControllerName = gCsmBlockIoControllerName;
            return EFI_SUCCESS;
        }
    }
    return EFI_UNSUPPORTED;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
