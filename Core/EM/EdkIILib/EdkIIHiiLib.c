/** @file
  HII Library implementation that uses DXE protocols and services.

  Copyright (c) 2006 - 2010, Intel Corporation<BR>
  All rights reserved. This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#pragma warning (disable : 4090)

#include <EdkIICommon.h>
#include <EdkIIHii.h>
#include <AmiDxeLib.h>
#include <Protocol/HiiDatabase.h>

/////////////////////////////////////////
/////////////////////////////////////////
/// IFR Functions
/////////////////////////////////////////
/////////////////////////////////////////

#define HII_LIB_OPCODE_ALLOCATION_SIZE  0x200

typedef struct {
  UINT8  *Buffer;
  UINTN  BufferSize;
  UINTN  Position;
} HII_LIB_OPCODE_BUFFER;

///
/// Lookup table that converts EFI_IFR_TYPE_X enum values to a width in bytes
///
GLOBAL_REMOVE_IF_UNREFERENCED CONST UINT8 mHiiDefaultTypeToWidth[] = {
  1, // EFI_IFR_TYPE_NUM_SIZE_8
  2, // EFI_IFR_TYPE_NUM_SIZE_16
  4, // EFI_IFR_TYPE_NUM_SIZE_32
  8, // EFI_IFR_TYPE_NUM_SIZE_64
  1, // EFI_IFR_TYPE_BOOLEAN
  3, // EFI_IFR_TYPE_TIME
  4, // EFI_IFR_TYPE_DATE
  2  // EFI_IFR_TYPE_STRING
};

static EFI_HII_DATABASE_PROTOCOL *gHiiDatabase = NULL;

/**
  Allocates and returns a new OpCode Handle.  OpCode Handles must be freed with 
  HiiFreeOpCodeHandle().

  @retval NULL   There are not enough resources to allocate a new OpCode Handle.
  @retval Other  A new OpCode handle.

**/
VOID *
EFIAPI
HiiAllocateOpCodeHandle (
  VOID
  )
{
  HII_LIB_OPCODE_BUFFER  *OpCodeBuffer;

  OpCodeBuffer = (HII_LIB_OPCODE_BUFFER *)AllocatePool (sizeof (HII_LIB_OPCODE_BUFFER));
  if (OpCodeBuffer == NULL) {
    return NULL;
  }
  OpCodeBuffer->Buffer = (UINT8 *)AllocatePool (HII_LIB_OPCODE_ALLOCATION_SIZE);
  if (OpCodeBuffer->Buffer == NULL) {
    FreePool (OpCodeBuffer);
    return NULL;
  }
  OpCodeBuffer->BufferSize = HII_LIB_OPCODE_ALLOCATION_SIZE;
  OpCodeBuffer->Position = 0;
  return (VOID *)OpCodeBuffer;
}

/**
  Frees an OpCode Handle that was previously allocated with HiiAllocateOpCodeHandle().
  When an OpCode Handle is freed, all of the opcodes associated with the OpCode
  Handle are also freed.

  If OpCodeHandle is NULL, then ASSERT().

  @param[in]  OpCodeHandle   Handle to the buffer of opcodes.

**/
VOID
EFIAPI
HiiFreeOpCodeHandle (
  VOID  *OpCodeHandle
  )
{
  HII_LIB_OPCODE_BUFFER  *OpCodeBuffer;

  ASSERT (OpCodeHandle != NULL);

  OpCodeBuffer = (HII_LIB_OPCODE_BUFFER *)OpCodeHandle;
  if (OpCodeBuffer->Buffer != NULL) {
    FreePool (OpCodeBuffer->Buffer);
  }
  FreePool (OpCodeBuffer);
}

/**
  Internal function gets the current position of opcode buffer.
  
  @param[in]  OpCodeHandle   Handle to the buffer of opcodes.

  @return Current position of opcode buffer.
**/
UINTN
EFIAPI
InternalHiiOpCodeHandlePosition (
  IN VOID  *OpCodeHandle
  )
{
  return ((HII_LIB_OPCODE_BUFFER  *)OpCodeHandle)->Position;
}

/**
  Internal function gets the start pointer of opcode buffer.
  
  @param[in]  OpCodeHandle   Handle to the buffer of opcodes.

  @return Pointer to the opcode buffer base.
**/
UINT8 *
EFIAPI
InternalHiiOpCodeHandleBuffer (
  IN VOID  *OpCodeHandle
  )
{
  return ((HII_LIB_OPCODE_BUFFER  *)OpCodeHandle)->Buffer;
}

/**
  Internal function reserves the enough buffer for current opcode.
  When the buffer is not enough, Opcode buffer will be extended.
  
  @param[in]  OpCodeHandle   Handle to the buffer of opcodes.
  @param[in]  Size           Size of current opcode.

  @return Pointer to the current opcode.
**/
UINT8 *
EFIAPI
InternalHiiGrowOpCodeHandle (
  IN VOID   *OpCodeHandle,
  IN UINTN  Size
  )
{
  HII_LIB_OPCODE_BUFFER  *OpCodeBuffer;
  UINT8                  *Buffer;

  ASSERT (OpCodeHandle != NULL);

  OpCodeBuffer = (HII_LIB_OPCODE_BUFFER *)OpCodeHandle;
  if (OpCodeBuffer->Position + Size > OpCodeBuffer->BufferSize) {
    Buffer = ReallocatePool (
              OpCodeBuffer->BufferSize, 
              OpCodeBuffer->BufferSize + (Size + HII_LIB_OPCODE_ALLOCATION_SIZE),
              OpCodeBuffer->Buffer
              );
    if (Buffer == NULL) {
      return NULL;
    }
    OpCodeBuffer->Buffer = Buffer;
    OpCodeBuffer->BufferSize += (Size + HII_LIB_OPCODE_ALLOCATION_SIZE);
  }
  Buffer = OpCodeBuffer->Buffer + OpCodeBuffer->Position;
  OpCodeBuffer->Position += Size;
  return Buffer;
}

/**
  Internal function creates opcode based on the template opcode.
  
  @param[in]  OpCodeHandle    Handle to the buffer of opcodes.
  @param[in]  OpCodeTemplate  Pointer to the template buffer of opcode.
  @param[in]  OpCode          OpCode IFR value.
  @param[in]  OpCodeSize      Size of opcode.
  @param[in]  ExtensionSize   Size of extended opcode.
  @param[in]  Scope           Scope bit of opcode.

  @return Pointer to the current opcode with opcode data.
**/
UINT8 *
EFIAPI
InternalHiiCreateOpCodeExtended (
  IN VOID   *OpCodeHandle,
  IN VOID   *OpCodeTemplate,
  IN UINT8  OpCode,
  IN UINTN  OpCodeSize,
  IN UINTN  ExtensionSize,
  IN UINT8  Scope
  )
{
  EFI_IFR_OP_HEADER  *Header;
  UINT8              *Buffer;

  ASSERT (OpCodeTemplate != NULL);
  ASSERT ((OpCodeSize + ExtensionSize) <= 0x7F);

  Header = (EFI_IFR_OP_HEADER *)OpCodeTemplate;
  Header->OpCode = OpCode;
  Header->Scope  = Scope;
  Header->Length = (UINT8)(OpCodeSize + ExtensionSize);
  Buffer = InternalHiiGrowOpCodeHandle (OpCodeHandle, Header->Length);
  return (UINT8 *)CopyMem (Buffer, Header, OpCodeSize);
}

/**
  Internal function creates opcode based on the template opcode for the normal opcode.
  
  @param[in]  OpCodeHandle    Handle to the buffer of opcodes.
  @param[in]  OpCodeTemplate  Pointer to the template buffer of opcode.
  @param[in]  OpCode          OpCode IFR value.
  @param[in]  OpCodeSize      Size of opcode.

  @return Pointer to the current opcode with opcode data.
**/
UINT8 *
EFIAPI
InternalHiiCreateOpCode (
  IN VOID   *OpCodeHandle,
  IN VOID   *OpCodeTemplate,
  IN UINT8  OpCode,
  IN UINTN  OpCodeSize
  )
{
  return InternalHiiCreateOpCodeExtended (OpCodeHandle, OpCodeTemplate, OpCode, OpCodeSize, 0, 0);
}

/**
  Append raw opcodes to an OpCodeHandle.

  If OpCodeHandle is NULL, then ASSERT().
  If RawBuffer is NULL, then ASSERT();

  @param[in]  OpCodeHandle   Handle to the buffer of opcodes.
  @param[in]  RawBuffer      Buffer of opcodes to append.
  @param[in]  RawBufferSize  The size, in bytes, of Buffer.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the appended opcodes.

**/
UINT8 *
EFIAPI
HiiCreateRawOpCodes (
  IN VOID   *OpCodeHandle,
  IN UINT8  *RawBuffer,
  IN UINTN  RawBufferSize
  )
{
  UINT8  *Buffer;

  ASSERT (RawBuffer != NULL);

  Buffer = InternalHiiGrowOpCodeHandle (OpCodeHandle, RawBufferSize);
  return (UINT8 *)CopyMem (Buffer, RawBuffer, RawBufferSize);
}

/**
  Append opcodes from one OpCode Handle to another OpCode handle.

  If OpCodeHandle is NULL, then ASSERT().
  If RawOpCodeHandle is NULL, then ASSERT();

  @param[in]  OpCodeHandle     Handle to the buffer of opcodes.
  @param[in]  RawOpCodeHandle  Handle to the buffer of opcodes.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the appended opcodes.

**/
UINT8 *
EFIAPI
InternalHiiAppendOpCodes (
  IN VOID  *OpCodeHandle,
  IN VOID  *RawOpCodeHandle
  )
{
  HII_LIB_OPCODE_BUFFER  *RawOpCodeBuffer;

  ASSERT (RawOpCodeHandle != NULL);

  RawOpCodeBuffer = (HII_LIB_OPCODE_BUFFER *)RawOpCodeHandle;
  return HiiCreateRawOpCodes (OpCodeHandle, RawOpCodeBuffer->Buffer, RawOpCodeBuffer->Position);
}

/**
  Create EFI_IFR_END_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().

  @param[in]  OpCodeHandle  Handle to the buffer of opcodes.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateEndOpCode (
  IN VOID  *OpCodeHandle
  )
{
  EFI_IFR_END  OpCode;

  return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_END_OP, sizeof (OpCode));
}

/**
  Create EFI_IFR_ONE_OF_OPTION_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If Type is invalid, then ASSERT().
  If Flags is invalid, then ASSERT().

  @param[in]  OpCodeHandle  Handle to the buffer of opcodes.
  @param[in]  StringId      StringId for the option
  @param[in]  Flags         Flags for the option
  @param[in]  Type          Type for the option
  @param[in]  Value         Value for the option

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateOneOfOptionOpCode (
  IN VOID    *OpCodeHandle,
  IN UINT16  StringId,
  IN UINT8   Flags,
  IN UINT8   Type,
  IN UINT64  Value
  )
{
  EFI_IFR_ONE_OF_OPTION  OpCode;

  ASSERT (Type < EFI_IFR_TYPE_OTHER);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Option = StringId;
  OpCode.Flags  = (UINT8) (Flags & (EFI_IFR_OPTION_DEFAULT | EFI_IFR_OPTION_DEFAULT_MFG));
  OpCode.Type   = Type;
  CopyMem (&OpCode.Value, &Value, mHiiDefaultTypeToWidth[Type]);

  return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_ONE_OF_OPTION_OP, sizeof (OpCode));
}

/**
  Create EFI_IFR_DEFAULT_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If Type is invalid, then ASSERT().

  @param[in]  OpCodeHandle  Handle to the buffer of opcodes.
  @param[in]  DefaultId     DefaultId for the default
  @param[in]  Type          Type for the default
  @param[in]  Value         Value for the default

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateDefaultOpCode (
  IN VOID    *OpCodeHandle,
  IN UINT16  DefaultId,
  IN UINT8   Type,
  IN UINT64  Value
  )
{
  EFI_IFR_DEFAULT  OpCode;

  ASSERT (Type < EFI_IFR_TYPE_OTHER);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Type      = Type;
  OpCode.DefaultId = DefaultId;
  CopyMem (&OpCode.Value, &Value, mHiiDefaultTypeToWidth[Type]);

  return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_DEFAULT_OP, sizeof (OpCode));
}

/**
  Create EFI_IFR_GUID opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If Guid is NULL, then ASSERT().
  If OpCodeSize < sizeof (EFI_IFR_GUID), then ASSERT().

  @param[in]  OpCodeHandle  Handle to the buffer of opcodes.
  @param[in]  Guid          Pointer to EFI_GUID of this guided opcode.
  @param[in]  GuidOpCode    Pointer to an EFI_IFR_GUID opcode.  This is an 
                            optional parameter that may be NULL.  If this
                            parameter is NULL, then the GUID extension 
                            region of the created opcode is filled with zeros.
                            If this parameter is not NULL, then the GUID 
                            extension region of GuidData will be copied to 
                            the GUID extension region of the created opcode.
  @param[in]  OpCodeSize    The size, in bytes, of created opcode.  This value 
                            must be >= sizeof(EFI_IFR_GUID).

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateGuidOpCode (
  IN VOID            *OpCodeHandle,
  IN CONST EFI_GUID  *Guid,
  IN CONST VOID      *GuidOpCode,    OPTIONAL
  IN UINTN           OpCodeSize
  )
{
  EFI_IFR_GUID  OpCode;
  EFI_IFR_GUID  *OpCodePointer;

  ASSERT (Guid != NULL);
  ASSERT (OpCodeSize >= sizeof (OpCode));

  ZeroMem (&OpCode, sizeof (OpCode));
  CopyGuid ((EFI_GUID *)(VOID *)&OpCode.Guid, Guid);

  OpCodePointer = (EFI_IFR_GUID *)InternalHiiCreateOpCodeExtended (
                                    OpCodeHandle, 
                                    &OpCode,
                                    EFI_IFR_GUID_OP,
                                    sizeof (OpCode),
                                    OpCodeSize - sizeof (OpCode),
                                    0
                                    );
  if (OpCodePointer != NULL && GuidOpCode != NULL) {
    CopyMem (OpCodePointer + 1, (EFI_IFR_GUID *)GuidOpCode + 1, OpCodeSize - sizeof (OpCode));
  }
  return (UINT8 *)OpCodePointer;
}

/**
  Create EFI_IFR_ACTION_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().

  @param[in]  OpCodeHandle  Handle to the buffer of opcodes.
  @param[in]  QuestionId      Question ID
  @param[in]  Prompt          String ID for Prompt
  @param[in]  Help            String ID for Help
  @param[in]  QuestionFlags   Flags in Question Header
  @param[in]  QuestionConfig  String ID for configuration

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateActionOpCode (
  IN VOID             *OpCodeHandle,
  IN EFI_QUESTION_ID  QuestionId,
  IN EFI_STRING_ID    Prompt,
  IN EFI_STRING_ID    Help,
  IN UINT8            QuestionFlags,
  IN EFI_STRING_ID    QuestionConfig
  )
{
  EFI_IFR_ACTION  OpCode;

  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.QuestionId    = QuestionId;
  OpCode.Question.Header.Prompt = Prompt;
  OpCode.Question.Header.Help   = Help;
  OpCode.Question.Flags         = QuestionFlags;
  OpCode.QuestionConfig         = QuestionConfig;

  return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_ACTION_OP, sizeof (OpCode));
}

/**
  Create EFI_IFR_SUBTITLE_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in Flags, then ASSERT().
  If Scope > 1, then ASSERT().

  @param[in]  OpCodeHandle  Handle to the buffer of opcodes.
  @param[in]  Prompt      String ID for Prompt
  @param[in]  Help        String ID for Help
  @param[in]  Flags       Subtitle opcode flags
  @param[in]  Scope       1 if this opcpde is the beginning of a new scope.
                          0 if this opcode is within the current scope.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateSubTitleOpCode (
  IN VOID           *OpCodeHandle,
  IN EFI_STRING_ID  Prompt,
  IN EFI_STRING_ID  Help,
  IN UINT8          Flags,
  IN UINT8          Scope
  )
{
  EFI_IFR_SUBTITLE  OpCode;

  ASSERT (Scope <= 1);
  ASSERT ((Flags & (~(EFI_IFR_FLAGS_HORIZONTAL))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Statement.Prompt = Prompt;
  OpCode.Statement.Help   = Help;
  OpCode.Flags            = Flags;

  return InternalHiiCreateOpCodeExtended (
           OpCodeHandle, 
           &OpCode,
           EFI_IFR_SUBTITLE_OP, 
           sizeof (OpCode), 
           0, 
           Scope
           );
}

/**
  Create EFI_IFR_REF_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().

  @param[in]  OpCodeHandle   Handle to the buffer of opcodes.
  @param[in]  FormId         Destination Form ID
  @param[in]  Prompt         String ID for Prompt
  @param[in]  Help           String ID for Help
  @param[in]  QuestionFlags  Flags in Question Header
  @param[in]  QuestionId     Question ID

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateGotoOpCode (
  IN VOID             *OpCodeHandle,
  IN EFI_FORM_ID      FormId,
  IN EFI_STRING_ID    Prompt,
  IN EFI_STRING_ID    Help,
  IN UINT8            QuestionFlags,
  IN EFI_QUESTION_ID  QuestionId
  )
{
  EFI_IFR_REF  OpCode;

  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.Header.Prompt = Prompt;
  OpCode.Question.Header.Help   = Help;
  OpCode.Question.QuestionId    = QuestionId;
  OpCode.Question.Flags         = QuestionFlags;
  OpCode.FormId                 = FormId;

  return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_REF_OP, sizeof (OpCode));
}

/**
  Create EFI_IFR_CHECKBOX_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().
  If any reserved bits are set in CheckBoxFlags, then ASSERT().

  @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
  @param[in]  QuestionId            Question ID
  @param[in]  VarStoreId            Storage ID
  @param[in]  VarOffset             Offset in Storage
  @param[in]  Prompt                String ID for Prompt
  @param[in]  Help                  String ID for Help
  @param[in]  QuestionFlags         Flags in Question Header
  @param[in]  CheckBoxFlags         Flags for checkbox opcode
  @param[in]  DefaultsOpCodeHandle  Handle for a buffer of DEFAULT opcodes.  This
                                    is an optional parameter that may be NULL.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateCheckBoxOpCode (
  IN VOID             *OpCodeHandle,
  IN EFI_QUESTION_ID  QuestionId,
  IN EFI_VARSTORE_ID  VarStoreId,
  IN UINT16           VarOffset,
  IN EFI_STRING_ID    Prompt,
  IN EFI_STRING_ID    Help,
  IN UINT8            QuestionFlags,
  IN UINT8            CheckBoxFlags,
  IN VOID             *DefaultsOpCodeHandle  OPTIONAL
  )
{
  EFI_IFR_CHECKBOX  OpCode;
  UINTN             Position;

  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.QuestionId             = QuestionId;
  OpCode.Question.VarStoreId             = VarStoreId;
  OpCode.Question.VarStoreInfo.VarOffset = VarOffset;
  OpCode.Question.Header.Prompt          = Prompt;
  OpCode.Question.Header.Help            = Help;
  OpCode.Question.Flags                  = QuestionFlags;
  OpCode.Flags                           = CheckBoxFlags;

  if (DefaultsOpCodeHandle == NULL) {
    return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_CHECKBOX_OP, sizeof (OpCode));
  }

  Position = InternalHiiOpCodeHandlePosition (OpCodeHandle);
  InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_CHECKBOX_OP, sizeof (OpCode), 0, 1);
  InternalHiiAppendOpCodes (OpCodeHandle, DefaultsOpCodeHandle);
  HiiCreateEndOpCode (OpCodeHandle);
  return InternalHiiOpCodeHandleBuffer (OpCodeHandle) + Position;
}

/**
  Create EFI_IFR_NUMERIC_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().
  If any reserved bits are set in NumericFlags, then ASSERT().

  @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
  @param[in]  QuestionId            Question ID
  @param[in]  VarStoreId            Storage ID
  @param[in]  VarOffset             Offset in Storage
  @param[in]  Prompt                String ID for Prompt
  @param[in]  Help                  String ID for Help
  @param[in]  QuestionFlags         Flags in Question Header
  @param[in]  NumericFlags          Flags for numeric opcode
  @param[in]  Minimum               Numeric minimum value
  @param[in]  Maximum               Numeric maximum value
  @param[in]  Step                  Numeric step for edit
  @param[in]  DefaultsOpCodeHandle  Handle for a buffer of DEFAULT opcodes.  This
                                    is an optional parameter that may be NULL.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateNumericOpCode (
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
  )
{
  EFI_IFR_NUMERIC  OpCode;
  UINTN            Position;

  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.QuestionId             = QuestionId;
  OpCode.Question.VarStoreId             = VarStoreId;
  OpCode.Question.VarStoreInfo.VarOffset = VarOffset;
  OpCode.Question.Header.Prompt          = Prompt;
  OpCode.Question.Header.Help            = Help;
  OpCode.Question.Flags                  = QuestionFlags;
  OpCode.Flags                           = NumericFlags;

  switch (NumericFlags & EFI_IFR_NUMERIC_SIZE) {
  case EFI_IFR_NUMERIC_SIZE_1:
    OpCode.data.u8.MinValue = (UINT8)Minimum;
    OpCode.data.u8.MaxValue = (UINT8)Maximum;
    OpCode.data.u8.Step     = (UINT8)Step;
    break;

  case EFI_IFR_NUMERIC_SIZE_2:
    OpCode.data.u16.MinValue = (UINT16)Minimum;
    OpCode.data.u16.MaxValue = (UINT16)Maximum;
    OpCode.data.u16.Step     = (UINT16)Step;
    break;

  case EFI_IFR_NUMERIC_SIZE_4:
    OpCode.data.u32.MinValue = (UINT32)Minimum;
    OpCode.data.u32.MaxValue = (UINT32)Maximum;
    OpCode.data.u32.Step     = (UINT32)Step;
    break;

  case EFI_IFR_NUMERIC_SIZE_8:
    OpCode.data.u64.MinValue = Minimum;
    OpCode.data.u64.MaxValue = Maximum;
    OpCode.data.u64.Step     = Step;
    break;
  }

  if (DefaultsOpCodeHandle == NULL) {
    return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_NUMERIC_OP, sizeof (OpCode));
  }

  Position = InternalHiiOpCodeHandlePosition (OpCodeHandle);
  InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_NUMERIC_OP, sizeof (OpCode), 0, 1);
  InternalHiiAppendOpCodes (OpCodeHandle, DefaultsOpCodeHandle);
  HiiCreateEndOpCode (OpCodeHandle);
  return InternalHiiOpCodeHandleBuffer (OpCodeHandle) + Position;
}

/**
  Create EFI_IFR_STRING_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().
  If any reserved bits are set in StringFlags, then ASSERT().

  @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
  @param[in]  QuestionId            Question ID
  @param[in]  VarStoreId            Storage ID
  @param[in]  VarOffset             Offset in Storage
  @param[in]  Prompt                String ID for Prompt
  @param[in]  Help                  String ID for Help
  @param[in]  QuestionFlags         Flags in Question Header
  @param[in]  StringFlags           Flags for string opcode
  @param[in]  MinSize               String minimum length
  @param[in]  MaxSize               String maximum length
  @param[in]  DefaultsOpCodeHandle  Handle for a buffer of DEFAULT opcodes.  This
                                    is an optional parameter that may be NULL.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateStringOpCode (
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
  )
{
  EFI_IFR_STRING  OpCode;
  UINTN           Position;

  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.Header.Prompt          = Prompt;
  OpCode.Question.Header.Help            = Help;
  OpCode.Question.QuestionId             = QuestionId;
  OpCode.Question.VarStoreId             = VarStoreId;
  OpCode.Question.VarStoreInfo.VarOffset = VarOffset;
  OpCode.Question.Flags                  = QuestionFlags;
  OpCode.MinSize                         = MinSize;
  OpCode.MaxSize                         = MaxSize;
  OpCode.Flags                           = (UINT8) (StringFlags & EFI_IFR_STRING_MULTI_LINE);

  if (DefaultsOpCodeHandle == NULL) {
    return InternalHiiCreateOpCode (OpCodeHandle, &OpCode, EFI_IFR_STRING_OP, sizeof (OpCode));
  }

  Position = InternalHiiOpCodeHandlePosition (OpCodeHandle);
  InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_STRING_OP, sizeof (OpCode), 0, 1);
  InternalHiiAppendOpCodes (OpCodeHandle, DefaultsOpCodeHandle);
  HiiCreateEndOpCode (OpCodeHandle);
  return InternalHiiOpCodeHandleBuffer (OpCodeHandle) + Position;
}

/**
  Create EFI_IFR_ONE_OF_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().
  If any reserved bits are set in OneOfFlags, then ASSERT().

  @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
  @param[in]  QuestionId            Question ID
  @param[in]  VarStoreId            Storage ID
  @param[in]  VarOffset             Offset in Storage
  @param[in]  Prompt                String ID for Prompt
  @param[in]  Help                  String ID for Help
  @param[in]  QuestionFlags         Flags in Question Header
  @param[in]  OneOfFlags            Flags for oneof opcode
  @param[in]  OptionsOpCodeHandle   Handle for a buffer of ONE_OF_OPTION opcodes.
  @param[in]  DefaultsOpCodeHandle  Handle for a buffer of DEFAULT opcodes.  This
                                    is an optional parameter that may be NULL.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateOneOfOpCode (
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
  )
{
  EFI_IFR_ONE_OF  OpCode;
  UINTN           Position;

  ASSERT (OptionsOpCodeHandle != NULL);
  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.Header.Prompt          = Prompt;
  OpCode.Question.Header.Help            = Help;
  OpCode.Question.QuestionId             = QuestionId;
  OpCode.Question.VarStoreId             = VarStoreId;
  OpCode.Question.VarStoreInfo.VarOffset = VarOffset;
  OpCode.Question.Flags                  = QuestionFlags;
  OpCode.Flags                           = OneOfFlags;

  Position = InternalHiiOpCodeHandlePosition (OpCodeHandle);
  InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_ONE_OF_OP, sizeof (OpCode), 0, 1);
  InternalHiiAppendOpCodes (OpCodeHandle, OptionsOpCodeHandle);
  if (DefaultsOpCodeHandle != NULL) {
    InternalHiiAppendOpCodes (OpCodeHandle, DefaultsOpCodeHandle);
  }
  HiiCreateEndOpCode (OpCodeHandle);
  return InternalHiiOpCodeHandleBuffer (OpCodeHandle) + Position;
}

/**
  Create EFI_IFR_ORDERED_LIST_OP opcode.

  If OpCodeHandle is NULL, then ASSERT().
  If any reserved bits are set in QuestionFlags, then ASSERT().
  If any reserved bits are set in OrderedListFlags, then ASSERT().

  @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
  @param[in]  QuestionId            Question ID
  @param[in]  VarStoreId            Storage ID
  @param[in]  VarOffset             Offset in Storage
  @param[in]  Prompt                String ID for Prompt
  @param[in]  Help                  String ID for Help
  @param[in]  QuestionFlags         Flags in Question Header
  @param[in]  OrderedListFlags      Flags for ordered list opcode
  @param[in]  DataType              Type for option value
  @param[in]  MaxContainers         Maximum count for options in this ordered list
  @param[in]  OptionsOpCodeHandle   Handle for a buffer of ONE_OF_OPTION opcodes.
  @param[in]  DefaultsOpCodeHandle  Handle for a buffer of DEFAULT opcodes.  This
                                    is an optional parameter that may be NULL.

  @retval NULL   There is not enough space left in Buffer to add the opcode.
  @retval Other  A pointer to the created opcode.

**/
UINT8 *
EFIAPI
HiiCreateOrderedListOpCode (
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
  )
{
  EFI_IFR_ORDERED_LIST  OpCode;
  UINTN                 Position;

  ASSERT (OptionsOpCodeHandle != NULL);
  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED | EFI_IFR_FLAG_OPTIONS_ONLY))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.Header.Prompt          = Prompt;
  OpCode.Question.Header.Help            = Help;
  OpCode.Question.QuestionId             = QuestionId;
  OpCode.Question.VarStoreId             = VarStoreId;
  OpCode.Question.VarStoreInfo.VarOffset = VarOffset;
  OpCode.Question.Flags                  = QuestionFlags;
  OpCode.MaxContainers                   = MaxContainers;
  OpCode.Flags                           = OrderedListFlags;

  Position = InternalHiiOpCodeHandlePosition (OpCodeHandle);
  InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_ORDERED_LIST_OP, sizeof (OpCode), 0, 1);
  InternalHiiAppendOpCodes (OpCodeHandle, OptionsOpCodeHandle);
  if (DefaultsOpCodeHandle != NULL) {
    InternalHiiAppendOpCodes (OpCodeHandle, DefaultsOpCodeHandle);
  }
  HiiCreateEndOpCode (OpCodeHandle);
  return InternalHiiOpCodeHandleBuffer (OpCodeHandle) + Position;
}

/**
  This is the internal worker function to update the data in
  a form specified by FormSetGuid, FormId and Label.

  @param[in] FormSetGuid       The optional Formset GUID.
  @param[in] FormId            The Form ID.
  @param[in] Package           The package header.
  @param[in] OpCodeBufferStart An OpCode buffer that contains the set of IFR 
                               opcodes to be inserted or replaced in the form.
  @param[in] OpCodeBufferEnd   An OpCcode buffer that contains the IFR opcode
                               that marks the end of a replace operation in the form.
  @param[out] TempPackage      The resultant package.

  @retval EFI_SUCCESS    The function completes successfully.
  @retval EFI_NOT_FOUND  The updated opcode or endopcode is not found.

**/
EFI_STATUS
EFIAPI
InternalHiiUpdateFormPackageData (
  IN  EFI_GUID               *FormSetGuid, OPTIONAL
  IN  EFI_FORM_ID            FormId,
  IN  EFI_HII_PACKAGE_HEADER *Package,
  IN  HII_LIB_OPCODE_BUFFER  *OpCodeBufferStart,
  IN  HII_LIB_OPCODE_BUFFER  *OpCodeBufferEnd,    OPTIONAL
  OUT EFI_HII_PACKAGE_HEADER *TempPackage
  )
{
  UINTN                     AddSize;
  UINT8                     *BufferPos;
  EFI_HII_PACKAGE_HEADER    PackageHeader;
  UINTN                     Offset;
  EFI_IFR_OP_HEADER         *IfrOpHdr;
  EFI_IFR_OP_HEADER         *UpdateIfrOpHdr;
  BOOLEAN                   GetFormSet;
  BOOLEAN                   GetForm;
  BOOLEAN                   Updated;
  UINTN                     UpdatePackageLength;

  CopyMem (TempPackage, Package, sizeof (EFI_HII_PACKAGE_HEADER));
  UpdatePackageLength = sizeof (EFI_HII_PACKAGE_HEADER);
  BufferPos           = (UINT8 *) (TempPackage + 1);

  CopyMem (&PackageHeader, Package, sizeof (EFI_HII_PACKAGE_HEADER));
  IfrOpHdr   = (EFI_IFR_OP_HEADER *)((UINT8 *) Package + sizeof (EFI_HII_PACKAGE_HEADER));
  Offset     = sizeof (EFI_HII_PACKAGE_HEADER);
  GetFormSet = (BOOLEAN) ((FormSetGuid == NULL) ? TRUE : FALSE);
  GetForm    = FALSE;
  Updated    = FALSE;

  while (Offset < PackageHeader.Length) {
    CopyMem (BufferPos, IfrOpHdr, IfrOpHdr->Length);
    BufferPos           += IfrOpHdr->Length;
    UpdatePackageLength += IfrOpHdr->Length;
    
    //
    // Find the matched FormSet and Form
    //
    if ((IfrOpHdr->OpCode == EFI_IFR_FORM_SET_OP) && (FormSetGuid != NULL)) {
      if (CompareGuid((EFI_GUID *)(VOID *)&((EFI_IFR_FORM_SET *) IfrOpHdr)->Guid, FormSetGuid)) {
        GetFormSet = TRUE;
      } else {
        GetFormSet = FALSE;
      }
    } else if (IfrOpHdr->OpCode == EFI_IFR_FORM_OP || IfrOpHdr->OpCode == EFI_IFR_FORM_MAP_OP) {
      if (CompareMem (&((EFI_IFR_FORM *) IfrOpHdr)->FormId, &FormId, sizeof (EFI_FORM_ID)) == 0) {
        GetForm = TRUE;
      } else {
        GetForm = FALSE;
      }
    }
    
    //
    // The matched Form is found, and Update data in this form
    //
    if (GetFormSet && GetForm) {
      UpdateIfrOpHdr = (EFI_IFR_OP_HEADER *) OpCodeBufferStart->Buffer;
      if ((UpdateIfrOpHdr->Length == IfrOpHdr->Length) && \
          (CompareMem (IfrOpHdr, UpdateIfrOpHdr, UpdateIfrOpHdr->Length) == 0)) {
        //
        // Remove the original data when End OpCode buffer exist.
        //
        if (OpCodeBufferEnd != NULL) {
          Offset        += IfrOpHdr->Length;
          IfrOpHdr       = (EFI_IFR_OP_HEADER *) ((UINT8 *) (IfrOpHdr) + IfrOpHdr->Length);
          UpdateIfrOpHdr = (EFI_IFR_OP_HEADER *) OpCodeBufferEnd->Buffer;
          while (Offset < PackageHeader.Length) {
            //
            // Search the matched end opcode
            //
            if ((UpdateIfrOpHdr->Length == IfrOpHdr->Length) && \
                (CompareMem (IfrOpHdr, UpdateIfrOpHdr, UpdateIfrOpHdr->Length) == 0)) {
              break;
            }
            //
            // Go to the next Op-Code
            //
            Offset        += IfrOpHdr->Length;
            IfrOpHdr       = (EFI_IFR_OP_HEADER *) ((UINT8 *) (IfrOpHdr) + IfrOpHdr->Length);
          }
          
          if (Offset >= PackageHeader.Length) {
            //
            // The end opcode is not found.
            //
            return EFI_NOT_FOUND;
          }
        }

        //
        // Insert the updated data
        //
        AddSize = ((EFI_IFR_OP_HEADER *) OpCodeBufferStart->Buffer)->Length;
        CopyMem (BufferPos, OpCodeBufferStart->Buffer + AddSize, OpCodeBufferStart->Position - AddSize);
        BufferPos           += OpCodeBufferStart->Position - AddSize;
        UpdatePackageLength += OpCodeBufferStart->Position - AddSize;

        if (OpCodeBufferEnd != NULL) {
          //
          // Add the end opcode
          //
          CopyMem (BufferPos, IfrOpHdr, IfrOpHdr->Length);
          BufferPos           += IfrOpHdr->Length;
          UpdatePackageLength += IfrOpHdr->Length;
        }

        //
        // Copy the left package data.
        //
        Offset += IfrOpHdr->Length;
        CopyMem (BufferPos, (UINT8 *) Package + Offset, PackageHeader.Length - Offset);
        UpdatePackageLength += PackageHeader.Length - Offset;

        //
        // Set update flag
        //
        Updated = TRUE;
        break;
      }
    }

    //
    // Go to the next Op-Code
    //
    Offset   += IfrOpHdr->Length;
    IfrOpHdr = (EFI_IFR_OP_HEADER *) ((CHAR8 *) (IfrOpHdr) + IfrOpHdr->Length);
  }
  
  if (!Updated) {
    //
    // The updated opcode buffer is not found.
    //
    return EFI_NOT_FOUND;
  }
  //
  // Update the package length.
  //
  PackageHeader.Length = (UINT32) UpdatePackageLength;
  CopyMem (TempPackage, &PackageHeader, sizeof (EFI_HII_PACKAGE_HEADER));

  return EFI_SUCCESS;
}

/**
  This function updates a form that has previously been registered with the HII 
  Database.  This function will perform at most one update operation.
    
  The form to update is specified by Handle, FormSetGuid, and FormId.  Binary 
  comparisons of IFR opcodes are performed from the beginning of the form being 
  updated until an IFR opcode is found that exactly matches the first IFR opcode 
  specified by StartOpCodeHandle.  The following rules are used to determine if
  an insert, replace, or delete operation is performed.
  
  1) If no matches are found, then NULL is returned.  
  2) If a match is found, and EndOpCodeHandle is NULL, then all of the IFR opcodes
     from StartOpCodeHandle except the first opcode are inserted immediately after 
     the matching IFR opcode in the form to be updated.
  3) If a match is found, and EndOpCodeHandle is not NULL, then a search is made 
     from the matching IFR opcode until an IFR opcode exactly matches the first 
     IFR opcode specified by EndOpCodeHandle.  If no match is found for the first
     IFR opcode specified by EndOpCodeHandle, then NULL is returned.  If a match
     is found, then all of the IFR opcodes between the start match and the end 
     match are deleted from the form being updated and all of the IFR opcodes
     from StartOpCodeHandle except the first opcode are inserted immediately after 
     the matching start IFR opcode.  If StartOpCcodeHandle only contains one
     IFR instruction, then the result of this operation will delete all of the IFR
     opcodes between the start end matches.

  If HiiHandle is NULL, then ASSERT().
  If StartOpCodeHandle is NULL, then ASSERT().

  @param[in]  HiiHandle          The HII Handle of the form to update.
  @param[in]  FormSetGuid        The Formset GUID of the form to update.  This
                                 is an optional parameter that may be NULL.
                                 If it is NULL, all FormSet will be updated.
  @param[in]  FormId             The ID of the form to update.
  @param[in]  StartOpCodeHandle  An OpCode Handle that contains the set of IFR 
                                 opcodes to be inserted or replaced in the form.
                                 The first IFR instruction in StartOpCodeHandle 
                                 is used to find matching IFR opcode in the 
                                 form. 
  @param[in]  EndOpCodeHandle    An OpCcode Handle that contains the IFR opcode
                                 that marks the end of a replace operation in
                                 the form.  This is an optional parameter that
                                 may be NULL.  If it is NULL, then an the IFR
                                 opcodes specified by StartOpCodeHandle are 
                                 inserted into the form.
  
  @retval EFI_OUT_OF_RESOURCES   No enough memory resource is allocated.
  @retval EFI_NOT_FOUND          The following cases will return EFI_NOT_FOUND.
                                 1) The form specified by HiiHandle, FormSetGuid, 
                                 and FormId could not be found in the HII Database.
                                 2) No IFR opcodes in the target form match the first
                                 IFR opcode in StartOpCodeHandle.
                                 3) EndOpCOde is not NULL, and no IFR opcodes in the 
                                 target form following a matching start opcode match 
                                 the first IFR opcode in EndOpCodeHandle.
  @retval EFI_SUCCESS            The matched form is updated by StartOpcode.

**/
EFI_STATUS
EFIAPI
HiiUpdateForm (
  IN EFI_HII_HANDLE  HiiHandle,           
  IN EFI_GUID        *FormSetGuid,        OPTIONAL
  IN EFI_FORM_ID     FormId,
  IN VOID            *StartOpCodeHandle,
  IN VOID            *EndOpCodeHandle     OPTIONAL
  )
{
  EFI_STATUS                   Status;
  EFI_HII_PACKAGE_LIST_HEADER  *HiiPackageList;
  UINT32                       PackageListLength;  
  UINT32                       Offset;
  EFI_HII_PACKAGE_LIST_HEADER  *UpdatePackageList;
  UINTN                        BufferSize;
  UINT8                        *UpdateBufferPos;
  EFI_HII_PACKAGE_HEADER       *Package;
  EFI_HII_PACKAGE_HEADER       *TempPacakge;
  EFI_HII_PACKAGE_HEADER       PackageHeader;
  BOOLEAN                      Updated;
  HII_LIB_OPCODE_BUFFER        *OpCodeBufferStart;
  HII_LIB_OPCODE_BUFFER        *OpCodeBufferEnd;
  
  //
  // Input update data can't be NULL.
  //
  ASSERT (HiiHandle != NULL);
  ASSERT (StartOpCodeHandle != NULL);
  UpdatePackageList = NULL;
  TempPacakge       = NULL;
  HiiPackageList    = NULL;
  
  //
  // Retrieve buffer data from Opcode Handle
  //
  OpCodeBufferStart = (HII_LIB_OPCODE_BUFFER *) StartOpCodeHandle;
  OpCodeBufferEnd   = (HII_LIB_OPCODE_BUFFER *) EndOpCodeHandle;

  if(gHiiDatabase == NULL) {
      Status = pBS->LocateProtocol(&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &gHiiDatabase);
      if(EFI_ERROR(Status))
          return Status;
  }
  
  //
  // Get the original package list
  //
  BufferSize = 0;
  HiiPackageList   = NULL;
  Status = gHiiDatabase->ExportPackageLists (gHiiDatabase, HiiHandle, &BufferSize, HiiPackageList);
  //
  // The return status should always be EFI_BUFFER_TOO_SMALL as input buffer's size is 0.
  //
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return Status;
  }

  HiiPackageList = AllocatePool (BufferSize);
  if (HiiPackageList == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Finish;
  }

  Status = gHiiDatabase->ExportPackageLists (gHiiDatabase, HiiHandle, &BufferSize, HiiPackageList);
  if (EFI_ERROR (Status)) {
    goto Finish;
  }

  //
  // Calculate and allocate space for retrieval of IFR data
  //
  BufferSize += OpCodeBufferStart->Position;
  UpdatePackageList = AllocateZeroPool (BufferSize);
  if (UpdatePackageList == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Finish;
  }
  
  //
  // Allocate temp buffer to store the temp updated package buffer
  //
  TempPacakge = AllocateZeroPool (BufferSize);
  if (TempPacakge == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Finish;
  }

  UpdateBufferPos = (UINT8 *) UpdatePackageList;

  //
  // Copy the package list header
  //
  CopyMem (UpdateBufferPos, HiiPackageList, sizeof (EFI_HII_PACKAGE_LIST_HEADER));
  UpdateBufferPos += sizeof (EFI_HII_PACKAGE_LIST_HEADER);
  
  //
  // Go through each package to find the matched package and update one by one
  //
  Updated = FALSE;
  Offset  = sizeof (EFI_HII_PACKAGE_LIST_HEADER);

//  PackageListLength = ReadUnaligned32 (&HiiPackageList->PackageLength);
  PackageListLength = HiiPackageList->PackageLength;

  while (Offset < PackageListLength) {
    Package = (EFI_HII_PACKAGE_HEADER *) (((UINT8 *) HiiPackageList) + Offset);
    CopyMem (&PackageHeader, Package, sizeof (EFI_HII_PACKAGE_HEADER));
    Offset += Package->Length;

    if (Package->Type == EFI_HII_PACKAGE_FORMS) {
      //
      // Check this package is the matched package.
      //
      Status = InternalHiiUpdateFormPackageData (FormSetGuid, FormId, Package, OpCodeBufferStart, OpCodeBufferEnd, TempPacakge);
      //
      // The matched package is found. Its package buffer will be updated by the input new data.
      //
      if (!EFI_ERROR(Status)) {
        //
        // Set Update Flag
        //        
        Updated = TRUE;
        //
        // Add updated package buffer
        //
        Package = TempPacakge;
      }
    }

    //
    // Add pacakge buffer
    //
    CopyMem (&PackageHeader, Package, sizeof (EFI_HII_PACKAGE_HEADER));
    CopyMem (UpdateBufferPos, Package, PackageHeader.Length);
    UpdateBufferPos += PackageHeader.Length;
  }
  
  if (Updated) {
    //
    // Update package list length
    //
    BufferSize = UpdateBufferPos - (UINT8 *) UpdatePackageList;

//    WriteUnaligned32 (&UpdatePackageList->PackageLength, (UINT32) BufferSize);
    UpdatePackageList->PackageLength = (UINT32) BufferSize;
    
    //
    // Update Package to show form
    //
    Status = gHiiDatabase->UpdatePackageList (gHiiDatabase, HiiHandle, UpdatePackageList);
  } else {
    //
    // Not matched form is found and updated.
    //
    Status = EFI_NOT_FOUND;
  }

Finish:
  if (HiiPackageList != NULL) {
    FreePool (HiiPackageList);
  }
  
  if (UpdatePackageList != NULL) {
    FreePool (UpdatePackageList);
  }
  
  if (TempPacakge != NULL) {
    FreePool (TempPacakge);
  }

  return Status; 
}

#pragma warning (default : 4090)
