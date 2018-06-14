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
// $Header: /Alaska/SOURCE/Core/EdkIICompLib/EdkIIHii.h 1     5/05/11 5:04p Artems $
//
// $Revision: 1 $
//
// $Date: 5/05/11 5:04p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EdkIICompLib/EdkIIHii.h $
// 
// 1     5/05/11 5:04p Artems
// EdkII compatibility library headers
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<EdkIIHii.h>
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EDKII_HII__H__
#define __EDKII_HII__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <UefiHii.h>

#define EFI_IFR_TIANO_GUID \
    { 0xf0b1735, 0x87a0, 0x4193, 0xb2, 0x66, 0x53, 0x8c, 0x38, 0xaf, 0x48, 0xce }

#define EFI_IFR_EXTEND_OP_LABEL       0x0


#pragma pack(1)
typedef struct _EFI_IFR_GUID_LABEL {
  EFI_IFR_OP_HEADER   Header;
  EFI_GUID            Guid;
  UINT8               ExtendOpCode;
  UINT16              Number;
} EFI_IFR_GUID_LABEL;
#pragma pack()

EFI_STRING HiiGetString(
    IN EFI_HII_HANDLE  HiiHandle,
    IN EFI_STRING_ID   StringId,
    IN CONST CHAR8     *Language  OPTIONAL
);

EFI_STRING_ID HiiSetString(
    IN EFI_HII_HANDLE HiiHandle,
    IN EFI_STRING_ID  StringId,            OPTIONAL
    IN EFI_STRING     String,
    IN CHAR8          *SupportedLanguages  OPTIONAL
);

EFI_STATUS HiiUpdateForm(
    IN EFI_HII_HANDLE  HiiHandle,           
    IN EFI_GUID        *FormSetGuid,        OPTIONAL
    IN EFI_FORM_ID     FormId,
    IN VOID            *StartOpCodeHandle,
    IN VOID            *EndOpCodeHandle     OPTIONAL
);

VOID* HiiAllocateOpCodeHandle(
    VOID
);

VOID HiiFreeOpCodeHandle(
    VOID  *OpCodeHandle
);

/*
EFI_HII_HANDLE HiiAddPackages(
    IN CONST EFI_GUID    *PackageListGuid,
    IN       EFI_HANDLE  DeviceHandle  OPTIONAL,
    ...
);
*/

UINT8* HiiCreateRawOpCodes (
    IN VOID   *OpCodeHandle,
    IN UINT8  *RawBuffer,
    IN UINTN  RawBufferSize
);

UINT8* HiiCreateEndOpCode (
    IN VOID  *OpCodeHandle
);

UINT8* HiiCreateOneOfOptionOpCode (
    IN VOID    *OpCodeHandle,
    IN UINT16  StringId,
    IN UINT8   Flags,
    IN UINT8   Type,
    IN UINT64  Value
);

UINT8* HiiCreateDefaultOpCode (
    IN VOID    *OpCodeHandle,
    IN UINT16  DefaultId,
    IN UINT8   Type,
    IN UINT64  Value
);

UINT8* HiiCreateActionOpCode(
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN EFI_STRING_ID    QuestionConfig
);

UINT8* HiiCreateGotoOpCode(
    IN VOID             *OpCodeHandle,
    IN EFI_FORM_ID      FormId,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN EFI_QUESTION_ID  QuestionId
);

UINT8* HiiCreateGuidOpCode (
    IN VOID            *OpCodeHandle,
    IN CONST EFI_GUID  *Guid,
    IN CONST VOID      *GuidOpCode,    OPTIONAL
    IN UINTN           OpCodeSize
);

UINT8* HiiCreateSubTitleOpCode (
    IN VOID           *OpCodeHandle,
    IN EFI_STRING_ID  Prompt,
    IN EFI_STRING_ID  Help,
    IN UINT8          Flags,
    IN UINT8          Scope
);

UINT8* HiiCreateCheckBoxOpCode (
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_VARSTORE_ID  VarStoreId,
    IN UINT16           VarOffset,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN UINT8            CheckBoxFlags,
    IN VOID             *DefaultsOpCodeHandle  OPTIONAL
);

UINT8* HiiCreateNumericOpCode (
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_VARSTORE_ID  VarStoreId,
    IN UINT16           VarOffset,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN UINT8            NumericFlags,
    IN UINT64           Minimum,
    IN UINT64           Maximum,
    IN UINT64           Step,
    IN VOID             *DefaultsOpCodeHandle  OPTIONAL
);

UINT8* HiiCreateStringOpCode (
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_VARSTORE_ID  VarStoreId,
    IN UINT16           VarOffset,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN UINT8            StringFlags,
    IN UINT8            MinSize,
    IN UINT8            MaxSize,
    IN VOID             *DefaultsOpCodeHandle  OPTIONAL
);

UINT8* HiiCreateOneOfOpCode (
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_VARSTORE_ID  VarStoreId,
    IN UINT16           VarOffset,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN UINT8            OneOfFlags,
    IN VOID             *OptionsOpCodeHandle,
    IN VOID             *DefaultsOpCodeHandle  OPTIONAL
);

UINT8* HiiCreateOrderedListOpCode (
    IN VOID             *OpCodeHandle,
    IN EFI_QUESTION_ID  QuestionId,
    IN EFI_VARSTORE_ID  VarStoreId,
    IN UINT16           VarOffset,
    IN EFI_STRING_ID    Prompt,
    IN EFI_STRING_ID    Help,
    IN UINT8            QuestionFlags,
    IN UINT8            OrderedListFlags,
    IN UINT8            DataType,
    IN UINT8            MaxContainers,
    IN VOID             *OptionsOpCodeHandle,
    IN VOID             *DefaultsOpCodeHandle  OPTIONAL
);





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