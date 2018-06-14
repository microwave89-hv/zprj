//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/CsmVideo/AmiMapping.c 2     3/04/11 2:28p Olegi $
//
// $Revision: 2 $
//
// $Date: 3/04/11 2:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/CsmVideo/AmiMapping.c $
// 
// 2     3/04/11 2:28p Olegi
// [TAG]  		EIP55098
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Install EFI_COMPONENT_NAME_PROTOCOL if BIOS is in UEFI
// 2.0 mode and EFI_COMPONENT_NAME2_PROTOCOL if BIOS is in UEFI 2.1 mode.
// [Files]  		UefiBiosVideo.h
// UefiBiosVideo.c
// ComponentName.c
// AmiMapping.h
// AmiMapping.c
// 
// 1     12/29/06 3:33p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiMapping.c
//
// Description:	Mapping from EDK to AMI definitions
//
//<AMI_FHDR_END>
//**********************************************************************
#include "AmiMapping.h"
#include "VgaMiniPort.h"

EFI_GUID gEfiVgaMiniPortProtocolGuid = EFI_VGA_MINI_PORT_PROTOCOL_GUID;

EFI_STATUS EfiLibInstallAllDriverProtocols (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable,
  IN EFI_DRIVER_BINDING_PROTOCOL        *DriverBinding,
  IN EFI_HANDLE                         DriverBindingHandle,
#if EFI_SPECIFICATION_VERSION <= 0x20000
  IN EFI_COMPONENT_NAME_PROTOCOL        *ComponentName,         OPTIONAL
#else
  IN EFI_COMPONENT_NAME2_PROTOCOL       *ComponentName,        OPTIONAL 
#endif
  IN VOID/*EFI_DRIVER_CONFIGURATION_PROTOCOL*/  *DriverConfiguration,  OPTIONAL
  IN VOID/*EFI_DRIVER_DIAGNOSTICS_PROTOCOL*/    *DriverDiagnostics     OPTIONAL
)
{
  EFI_STATUS Status;
  InitAmiLib (ImageHandle, SystemTable);
  DriverBinding->ImageHandle = ImageHandle;
  DriverBinding->DriverBindingHandle = DriverBindingHandle;
  Status = gBS->InstallMultipleProtocolInterfaces (
                &DriverBinding->DriverBindingHandle,
                &gEfiDriverBindingProtocolGuid, DriverBinding,
				NULL
              );
  if (EFI_ERROR(Status)) return Status;
  if (ComponentName)
    Status = gBS->InstallMultipleProtocolInterfaces (
                  &DriverBinding->DriverBindingHandle,
#if EFI_SPECIFICATION_VERSION <= 0x20000
				  &gEfiComponentNameProtocolGuid, ComponentName,
#else
                  &gEfiComponentName2ProtocolGuid,ComponentName,
#endif  
				  NULL
                );
  return Status;
}

BOOLEAN
EfiLibCompareLanguage (
  CHAR8  *Language1,
  CHAR8  *Language2
  )

{
	return    *(UINT16*)Language1==*(UINT16*)Language2
		   && Language1[2]==Language2[2];
}

EFI_STATUS EfiLibLookupUnicodeString (
  CHAR8                     *Language,
  CHAR8                     *SupportedLanguages,
  EFI_UNICODE_STRING_TABLE  *UnicodeStringTable,
  CHAR16                    **UnicodeString
  )
{
  //
  // Make sure the parameters are valid
  //
  if (Language == NULL || UnicodeString == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // If there are no supported languages, or the Unicode String Table is empty, then the 
  // Unicode String specified by Language is not supported by this Unicode String Table
  //
  if (SupportedLanguages == NULL || UnicodeStringTable == NULL) {
    return EFI_UNSUPPORTED;
  }

  //
  // Make sure Language is in the set of Supported Languages
  //
  while (*SupportedLanguages != 0) {
    if (EfiLibCompareLanguage (Language, SupportedLanguages)) {

      //
      // Search the Unicode String Table for the matching Language specifier
      //
      while (UnicodeStringTable->Language != NULL) {
        if (EfiLibCompareLanguage (Language, UnicodeStringTable->Language)) {

          //
          // A matching string was found, so return it
          //
          *UnicodeString = UnicodeStringTable->UnicodeString;
          return EFI_SUCCESS;
        }
        UnicodeStringTable++;
      }
      return EFI_UNSUPPORTED;
    }
    SupportedLanguages += 3;
  }
  return EFI_UNSUPPORTED;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************