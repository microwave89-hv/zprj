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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/CsmVideo/AmiMapping.h 3     12/23/13 10:21a Olegi $
//
// $Revision: 3 $
//
// $Date: 12/23/13 10:21a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/CsmVideo/AmiMapping.h $
// 
// 3     12/23/13 10:21a Olegi
// [TAG]  		EIP148123
// [Description]  	CSM includes file which name has been changed
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
// Name:	AmiMapping.h
//
// Description:	Mapping from EDK to AMI definitions
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AMI_MAPPING__H__
#define __AMI_MAPPING__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName.h>
#include <AmiDxeLib.h>
#include <Token.h>

#define STATIC static
#define EFI_GUID_DEFINITION(a)
#define EFI_PROTOCOL_DEFINITION(a) CONVERT_TO_STRING(Protocol/a.h)
#define EFI_DRIVER_ENTRY_POINT(a)
#define EFI_TPL_NOTIFY TPL_NOTIFY
#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))

#define EfiZeroMem(Address, Length) gBS->SetMem  ((Address), (Length), 0)
#define gBS pBS
#define ReportStatusCodeWithDevicePath(a,b,c,d,e)

#define ACPI_ADR_DISPLAY_TYPE_VGA               1
#define ACPI_DISPLAY_ADR(_DeviceIdScheme, _HeadId, _NonVgaOutput, _BiosCanDetect, _VendorInfo, _Type, _Port, _Index) \
          ((UINT32) ( (((_DeviceIdScheme) & 0x1) << 31) |  \
                      (((_HeadId)         & 0x7) << 18) |  \
                      (((_NonVgaOutput)   & 0x1) << 17) |  \
                      (((_BiosCanDetect)  & 0x1) << 16) |  \
                      (((_VendorInfo)     & 0xf) << 12) |  \
                      (((_Type)           & 0xf) << 8)  |  \
                      (((_Port)           & 0xf) << 4)  |  \
                       ((_Index)          & 0xf) ))
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION < 0x4028F)
#define SetDevicePathNodeLength SET_NODE_LENGTH
#endif

#define EfiAppendDevicePathNode DPAddNode
#define CR(pField, OutterType, Field, Signature) OUTTER(pField, Field, OutterType)
#define EFI_SEGMENT(_Adr)     (UINT16) ((UINT16) (((UINTN) (_Adr)) >> 4) & 0xf000)
#define EFI_OFFSET(_Adr)      (UINT16) (((UINT16) ((UINTN) (_Adr))) & 0xffff)
#define EFI_SIMPLE_TEXT_OUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
#define EFI_SIMPLE_TEXT_OUTPUT_MODE SIMPLE_TEXT_OUTPUT_MODE
#define CHAR_NULL             0x0000
#define CHAR_BACKSPACE        0x0008
#define CHAR_TAB              0x0009
#define CHAR_LINEFEED         0x000A
#define CHAR_CARRIAGE_RETURN  0x000D

typedef struct {
  CHAR8   *Language;
  CHAR16  *UnicodeString;
} EFI_UNICODE_STRING_TABLE;

#define INSTALL_ALL_DRIVER_PROTOCOLS EfiLibInstallAllDriverProtocols
EFI_STATUS
EfiLibInstallAllDriverProtocols (
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
  );

EFI_STATUS
EfiLibLookupUnicodeString (
  CHAR8                     *Language,
  CHAR8                     *SupportedLanguages,
  EFI_UNICODE_STRING_TABLE  *UnicodeStringTable,
  CHAR16                    **UnicodeString
  );

EFI_STATUS
EFIAPI
VgaClassDriverEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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