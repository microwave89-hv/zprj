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
// $Header: /Alaska/BIN/Core/Include/Protocol/UnicodeCollation.h 6     6/16/11 3:22p Felixp $
//
// $Revision: 6 $
//
// $Date: 6/16/11 3:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/UnicodeCollation.h $
// 
// 6     6/16/11 3:22p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 5     5/27/11 5:53p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 4     8/28/09 12:22p Felixp
// Support for both UnicodeCollation and UnicodeCollation2 protocols 
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     2/15/05 5:01p Felixp
// SpecialChars array definition removed
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     12/22/04 4:50p Radhikav
// removed unwanted comments.
// 
// 1     10/05/04 2:50p Radhikav
// Initial check in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: UnicodeCollation.h
//
// Description: UnicodeCollation Protocol Definition.
//
//<AMI_FHDR_END>
//***********************************************************************
#ifndef __UNICODE_COLLATION_PROTOCOL_H__
#define __UNICODE_COLLATION_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_UNICODE_COLLATION_PROTOCOL_GUID \
  { 0x1d85cd7f, 0xf43d, 0x11d2, 0x9a, 0x0c,  0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d }

GUID_VARIABLE_DECLARATION(gEfiUnicodeCollationProtocolGuid,EFI_UNICODE_COLLATION_PROTOCOL_GUID);

typedef	struct _EFI_UNICODE_COLLATION_PROTOCOL EFI_UNICODE_COLLATION_PROTOCOL;

// Protocol member functions
typedef
INTN
(EFIAPI *EFI_UNICODE_COLLATION_STRICOLL) (
  IN EFI_UNICODE_COLLATION_PROTOCOL	 	*This,
  IN CHAR16                          	*S1,
  IN CHAR16                           	*S2
  );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_COLLATION_METAIMATCH) (
  IN EFI_UNICODE_COLLATION_PROTOCOL	 		*This,
  IN CHAR16                                 *String,
  IN CHAR16                                 *Pattern
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_STRLWR) (
  IN EFI_UNICODE_COLLATION_PROTOCOL	 		*This,
  IN OUT CHAR16                             *String
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_STRUPR) (
  IN EFI_UNICODE_COLLATION_PROTOCOL	 		*This,
  IN OUT CHAR16                             *String
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_FATTOSTR) (
  IN EFI_UNICODE_COLLATION_PROTOCOL	 		*This,
  IN UINTN                                  FatSize,
  IN CHAR8                                  *Fat,
  OUT CHAR16                                *String
  );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_COLLATION_STRTOFAT) (
  IN EFI_UNICODE_COLLATION_PROTOCOL	 		*This,
  IN CHAR16                                 *String,
  IN UINTN                                  FatSize,
  OUT CHAR8                                 *Fat
  );

struct _EFI_UNICODE_COLLATION_PROTOCOL {
  EFI_UNICODE_COLLATION_STRICOLL                StriColl;
  EFI_UNICODE_COLLATION_METAIMATCH              MetaiMatch;
  EFI_UNICODE_COLLATION_STRLWR                  StrLwr;
  EFI_UNICODE_COLLATION_STRUPR                  StrUpr;
  EFI_UNICODE_COLLATION_FATTOSTR                FatToStr;
  EFI_UNICODE_COLLATION_STRTOFAT                StrToFat;
  CHAR8										    *SupportedLanguages;
};

//********************* Unicode Collation 2 Protocol ******************/
#if EFI_SPECIFICATION_VERSION<=0x20000
#define  EFI_UNICODE_COLLATION_PROTOCOL2_GUID EFI_UNICODE_COLLATION_PROTOCOL_GUID
#else //if EFI_SPECIFICATION_VERSION
#define EFI_UNICODE_COLLATION_PROTOCOL2_GUID \
    {0xa4c751fc, 0x23ae, 0x4c3e, 0x92, 0xe9, 0x49, 0x64, 0xcf, 0x63, 0xf3, 0x49}
#endif //if EFI_SPECIFICATION_VERSION
GUID_VARIABLE_DECLARATION(gEfiUnicodeCollation2ProtocolGuid,EFI_UNICODE_COLLATION_PROTOCOL2_GUID);

#if BACKWARD_COMPATIBLE_MODE
//UEFI 2.3 uses GUID identifier EFI_UNICODE_COLLATION_PROTOCOL2_GUID.
//According to UEFI naming convension it should be EFI_UNICODE_COLLATION2_PROTOCOL_GUID
#define EFI_UNICODE_COLLATION2_PROTOCOL_GUID EFI_UNICODE_COLLATION_PROTOCOL2_GUID
typedef EFI_UNICODE_COLLATION_PROTOCOL EFI_UNICODE_COLLATION2_PROTOCOL;
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
