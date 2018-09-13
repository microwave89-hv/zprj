//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Expression.c $
//
// $Author: Arunsb $
//
// $Revision: 18 $
//
// $Date: 6/10/13 12:06p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Expression.c $
// 
// 18    6/10/13 12:06p Arunsb
// EIP122907. Support for pushthis condition in inconsistent and
// nosubmitif
// 
// 17    4/17/13 12:29p Arunsb
// [TAG]  		EIP111063 
// [Category]  	Improvement
// [Description]  	Support for EFI_IFR_QUESTION_REF3_2 and
// EFI_IFR_QUESTION_REF3_3 opcodes
// [Files]  		Expression.c
// 
// 16    4/02/13 8:05a Arunsb
// [TAG]  		EIP113919, EIP114842
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_WRITE, EFI_IFR_READ,
// EFI_IFR_GET, EFI_IFR_SET and EFI_IFR_MAP_OP.
// [Files]  		Setupdata.h, ctrlcond.c, expression.c, hii.c and parse.c
// 
// 15    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 12    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 14    5/29/12 4:44a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 13    12/01/11 1:35a Premkumara
// [TAG]  		EIP73236
// [Category]  	Improvement
// [Description]  	Large amounts of allocated memory are not freed
// [Files]  		Expression.c, PopupEdit.c, Popup.c, MessageBox.c, Menu.c,
// Memo.c, 
// 
// 12    11/28/11 2:08a Premkumara
// [TAG]  		EIP75384 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		UefiWapper.c, Hii.c, Expression.c, CtrlCond.c, PopupSel.c,
// Minisetupext.c, Menu.c, Date.c, Ezport\Stylecommon.c,
// EzportPlus\StyleCommon.c,
// 
// 11    6/20/11 10:36a Rajashakerg
// [TAG]  		EIP56355 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_VERSION opcode	
// [Files]  		Expression.c
// 
// 10    3/18/11 9:41a Rajashakerg
// [TAG]  		EIP56355
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_VERSION opcode
// [Files]  		Expression.c
// 
// 9     2/03/11 8:19p Madhans
// [TAG] - EIP 50956   
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- If we leave the Setup page for 2 or more days. The system
// may hang/Crash.
// [Rootcause] - Memory leaks
// [Solution]- Memeory freed.
// [Files] - ctrlcond.c, memo.c and expression.c 
// 
// 8     12/02/10 2:38p Madhans
// [TAG] - EIP 48169  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Code Cleanup and Compiler Warning need to resolved.
// [Rootcause] Warnings reported when we build AMI higher Warning level.
// [Solution]- 1. Fix the warnings and do the code cleanup. 
//             2. Introduce proper checks.
//             3. change the popupSel.c to not change the Option/variable
// cache to default or first option
//                when the variable cache is not matching with any of
// option.
// [Files] - commonoem.c bbs.c boot.c hiistring.c resource.c
// popuppassword.c popupsel.c
//           expression.c hii.c parse.c
// 
// 8     8/18/10 5:58p Mallikarjunanv
// EIP-42300: Handled dataWidth to solve the hanging issue with respect to
// password updates
// 
// 7     7/07/10 7:45p Madhans
// Changes to Support Adding Conditions to Suppress or Grayout the Special
// controls.
// 
// 6     3/11/10 5:41p Madhans
// Coding Standards Update
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          Expression.C
//
// Description:	 Expression evaluation.
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
#include "Minisetup.h"
#include "TseUefiHii.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// In Aptio UnicodeCollation2 protocol is supported in the same file as
// UnicodeCollation Protocol depending on EFI_SPECIFICATION_VERSION
//
#ifndef TSE_FOR_APTIO_4_50
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation2)
#else
#if TSE_USE_EDK_LIBRARY
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation2)
#else
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation)
#endif
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define EXPRESSION_STACK_SIZE_INCREMENT 100
#define NewString(a, b) HiiAddString(b, a)
#define GetToken(a,b) HiiGetString(b, a)
//---------------------------------------------------------------------------

//
// Global stack used to evaluate boolean expresions
//
EFI_HII_VALUE *mOpCodeScopeStack = NULL;
EFI_HII_VALUE *mOpCodeScopeStackEnd = NULL;
EFI_HII_VALUE *mOpCodeScopeStackPointer = NULL;

EFI_HII_VALUE *mExpressionEvaluationStack = NULL;
EFI_HII_VALUE *mExpressionEvaluationStackEnd = NULL;
EFI_HII_VALUE *mExpressionEvaluationStackPointer = NULL;

CHAR16 *gEmptyString = L"";
VOID *gInconsistCondPtr = NULL;
//
// Unicode collation protocol interface
//
EFI_UNICODE_COLLATION2_PROTOCOL *mUnicodeCollation = NULL;

extern EFI_STATUS GetStringFromDevPath(EFI_DEVICE_PATH_PROTOCOL *DevPath, CHAR16 **DevPathStr);
extern EFI_STATUS GetDevPathFromHandle(EFI_HII_HANDLE HiiHandle, EFI_DEVICE_PATH_PROTOCOL **DevicePath);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  GrowStack
//
// Description:   Grow size of the stack
//
// Parameter:	  Stack     - On input: old stack; On output: new stack
//   			  StackPtr  - On input: old stack pointer; On output: new stack pointer
//  			  StackPtr  - On input: old stack end; On output: new stack end
//
// Return value:  EFI_SUCCESS          - Grow stack success.
//				  EFI_OUT_OF_RESOURCES - No enough memory for stack space.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

STATIC
EFI_STATUS
GrowStack (
  IN OUT EFI_HII_VALUE  **Stack,
  IN OUT EFI_HII_VALUE  **StackPtr,
  IN OUT EFI_HII_VALUE  **StackEnd
  )
{
  UINTN           Size;
  EFI_HII_VALUE  *NewStack;

  Size = EXPRESSION_STACK_SIZE_INCREMENT;
  if (*StackPtr != NULL) {
    Size = Size + (*StackEnd - *Stack);
  }

  NewStack = EfiLibAllocatePool (Size * sizeof (EFI_HII_VALUE));
  if (NewStack == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (*StackPtr != NULL) {
    //
    // Copy from Old Stack to the New Stack
    //
    EfiCopyMem (
      NewStack,
      *Stack,
      (*StackEnd - *Stack) * sizeof (EFI_HII_VALUE)
      );

    //
    // Free The Old Stack
    //
    gBS->FreePool (*Stack);
  }

  //
  // Make the Stack pointer point to the old data in the new stack
  //
  *StackPtr = NewStack + (*StackPtr - *Stack);
  *Stack    = NewStack;
  *StackEnd = NewStack + Size;

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  PushStack
//
// Description:   Push an element onto the Boolean Stack
//
// Parameter:	  Stack     - On input: old stack; On output: new stack
//				  StackPtr  - On input: old stack pointer; On output: new stack pointer
//				  StackPtr  - On input: old stack end; On output: new stack end
//				  Data      - Data to push.
//
// Return value:  EFI_SUCCESS - Push stack success.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PushStack (
  IN OUT EFI_HII_VALUE       **Stack,
  IN OUT EFI_HII_VALUE       **StackPtr,
  IN OUT EFI_HII_VALUE       **StackEnd,
  IN EFI_HII_VALUE           *Data
  )
{
  EFI_STATUS  Status;

  //
  // Check for a stack overflow condition
  //
  if (*StackPtr >= *StackEnd) {
    //
    // Grow the stack
    //
    Status = GrowStack (Stack, StackPtr, StackEnd);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  // Push the item onto the stack
  //
  EfiCopyMem (*StackPtr, Data, sizeof (EFI_HII_VALUE));
  *StackPtr = *StackPtr + 1;

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  PopStack
//
// Description:  Pop an element from the stack.
//
// Parameter:	  Stack     - On input: old stack; On output: new stack
//				  StackPtr  - On input: old stack pointer; On output: new stack pointer
//				  StackPtr  - On input: old stack end; On output: new stack end
//				  Data      - Data to pop.
//
// Return value:    EFI_SUCCESS       - The value was popped onto the stack.
//					EFI_ACCESS_DENIED - The pop operation underflowed the stack
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PopStack (
  IN OUT EFI_HII_VALUE       **Stack,
  IN OUT EFI_HII_VALUE       **StackPtr,
  IN OUT EFI_HII_VALUE       **StackEnd,
  OUT EFI_HII_VALUE          *Data
  )
{
  //
  // Check for a stack underflow condition
  //
  if (*StackPtr == *Stack) {
    return EFI_ACCESS_DENIED;
  }

  //
  // Pop the item off the stack
  //
  *StackPtr = *StackPtr - 1;
  EfiCopyMem (Data, *StackPtr, sizeof (EFI_HII_VALUE));
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	 ResetScopeStack
//
// Description:  Reset stack pointer to begin of the stack.
//
// Parameter:	 None.
//
// Return value: None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ResetScopeStack (
  VOID
  )
{
  mOpCodeScopeStackPointer = mOpCodeScopeStack;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  PushScope
//
// Description:   Push an Operand onto the Stack
//
// Parameter:	  Operand to push.
//
// Return value:  EFI_SUCCESS          - The value was pushed onto the stack.
//				  EFI_OUT_OF_RESOURCES - There is not enough system memory to grow the stack.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PushScope (
  IN UINT8   Operand
  )
{
  EFI_HII_VALUE  Data;

  Data.Type = EFI_IFR_TYPE_NUM_SIZE_8;
  Data.Value.u8 = Operand;

  return PushStack (
           &mOpCodeScopeStack,
           &mOpCodeScopeStackPointer,
           &mOpCodeScopeStackEnd,
           &Data
           );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  PopScope
//
// Description:   Pop an Operand from the Stack
//
// Parameter:	  Operand to pop.
//
// Return value:  EFI_SUCCESS          - The value was pushed onto the stack.
//				  EFI_OUT_OF_RESOURCES - There is not enough system memory to
//										 grow the stack.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PopScope (
  OUT UINT8     *Operand
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Data;

  Status = PopStack (
             &mOpCodeScopeStack,
             &mOpCodeScopeStackPointer,
             &mOpCodeScopeStackEnd,
             &Data
             );

  *Operand = Data.Value.u8;

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  ResetExpressionStack
//
// Description:   Reset stack pointer to begin of the stack.
//
// Parameter:	  None.
//
// Return value:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ResetExpressionStack (
  VOID
  )
{
  mExpressionEvaluationStackPointer = mExpressionEvaluationStack;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  PushExpression
//
// Description:   Push an Expression value onto the Stack
//
// Parameter:	  Value - Expression value to push.
//
// Return value:  EFI_SUCCESS          - The value was pushed onto the stack.
//				  EFI_OUT_OF_RESOURCES - There is not enough system memory to grow the stack.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PushExpression (
  IN EFI_HII_VALUE  *Value
  )
{
  return PushStack (
           &mExpressionEvaluationStack,
           &mExpressionEvaluationStackPointer,
           &mExpressionEvaluationStackEnd,
           Value
           );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  PopExpression
//
// Description:   Pop an Expression value from the Stack
//
// Parameter:	  Value - Expression value to pop.
//
// Return value:  EFI_SUCCESS          - The value was popped onto the stack.
//				  EFI_OUT_OF_RESOURCES - The pop operation underflowed the stack
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PopExpression (
  OUT EFI_HII_VALUE  *Value
  )
{
  return PopStack (
           &mExpressionEvaluationStack,
           &mExpressionEvaluationStackPointer,
           &mExpressionEvaluationStackEnd,
           Value
           );
}

/*
FORM_BROWSER_FORM *
IdToForm (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN UINT16                FormId
)
/*++

Routine Description:
  Get Form given its FormId.

Arguments:
  FormSet - The formset which contains this form.
  FormId  - Id of this form.

Returns:
  Pointer - The form.
  NULL    - Specified Form is not found in the formset.

--* /
{
  EFI_LIST_ENTRY     *Link;
  FORM_BROWSER_FORM  *Form;

  Link = GetFirstNode (&FormSet->FormListHead);
  while (!IsNull (&FormSet->FormListHead, Link)) {
    Form = FORM_BROWSER_FORM_FROM_LINK (Link);

    if (Form->FormId == FormId) {
      return Form;
    }

    Link = GetNextNode (&FormSet->FormListHead, Link);
  }

  return NULL;
}

FORM_BROWSER_STATEMENT *
IdToQuestion2 (
  IN FORM_BROWSER_FORM  *Form,
  IN UINT16             QuestionId
  )
/*++

Routine Description:
  Search a Question in Form scope using its QuestionId.

Arguments:
  Form        - The form which contains this Question.
  QuestionId  - Id of this Question.

Returns:
  Pointer - The Question.
  NULL    - Specified Question not found in the form.

--* /
{
  EFI_LIST_ENTRY          *Link;
  FORM_BROWSER_STATEMENT  *Question;

  if (QuestionId == 0) {
    //
    // The value of zero is reserved
    //
    return NULL;
  }

  Link = GetFirstNode (&Form->StatementListHead);
  while (!IsNull (&Form->StatementListHead, Link)) {
    Question = FORM_BROWSER_STATEMENT_FROM_LINK (Link);

    if (Question->QuestionId == QuestionId) {
      return Question;
    }

    Link = GetNextNode (&Form->StatementListHead, Link);
  }

  return NULL;
}

FORM_BROWSER_STATEMENT *
IdToQuestion (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN FORM_BROWSER_FORM     *Form,
  IN UINT16                QuestionId
  )
/*++

Routine Description:
  Search a Question in Formset scope using its QuestionId.

Arguments:
  FormSet     - The formset which contains this form.
  Form        - The form which contains this Question.
  QuestionId  - Id of this Question.

Returns:
  Pointer - The Question.
  NULL    - Specified Question not found in the form.

--* /
{
  EFI_LIST_ENTRY          *Link;
  FORM_BROWSER_STATEMENT  *Question;

  //
  // Search in the form scope first
  //
  Question = IdToQuestion2 (Form, QuestionId);
  if (Question != NULL) {
    return Question;
  }

  //
  // Search in the formset scope
  //
  Link = GetFirstNode (&FormSet->FormListHead);
  while (!IsNull (&FormSet->FormListHead, Link)) {
    Form = FORM_BROWSER_FORM_FROM_LINK (Link);

    Question = IdToQuestion2 (Form, QuestionId);
    if (Question != NULL) {
      return Question;
    }

    Link = GetNextNode (&FormSet->FormListHead, Link);
  }

  return NULL;
}

FORM_EXPRESSION *
RuleIdToExpression (
  IN FORM_BROWSER_FORM  *Form,
  IN UINT8              RuleId
  )
/*++

Routine Description:
  Get Expression given its RuleId.

Arguments:
  Form    - The form which contains this Expression.
  RuleId  - Id of this Expression.

Returns:
  Pointer - The Expression.
  NULL    - Specified Expression not found in the form.

--* /
{
  EFI_LIST_ENTRY   *Link;
  FORM_EXPRESSION  *Expression;

  Link = GetFirstNode (&Form->ExpressionListHead);
  while (!IsNull (&Form->ExpressionListHead, Link)) {
    Expression = FORM_EXPRESSION_FROM_LINK (Link);

    if (Expression->Type == EFI_HII_EXPRESSION_RULE && Expression->RuleId == RuleId) {
      return Expression;
    }

    Link = GetNextNode (&Form->ExpressionListHead, Link);
  }

  return NULL;
}
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  InitializeUnicodeCollationProtocol
//
// Description:   Locate the Unicode Collation Protocol interface for later use.
//
// Parameter:	  None
//
// Return value:  EFI_SUCCESS - Protocol interface initialize success.
//				  Other       - Protocol interface initialize failed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitializeUnicodeCollationProtocol (
  VOID
  )
{
  EFI_STATUS  Status;

  if (mUnicodeCollation != NULL) {
    return EFI_SUCCESS;
  }

  //
  // BUGBUG: Proper impelmentation is to locate all Unicode Collation Protocol
  // instances first and then select one which support English language.
  // Current implementation just pick the first instance.
  //
  Status = gBS->LocateProtocol (
                  &gEfiUnicodeCollation2ProtocolGuid,
                  NULL,
                  &mUnicodeCollation
                  );
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  IfrStrToUpper
//
// Description:function to conver the lower case string to upper
//
// Parameter:
//
// Return value:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
IfrStrToUpper (
  CHAR16                   *String
  )
{
  while (*String != 0) {
    if ((*String >= 'a') && (*String <= 'z')) {
      *String = (*String) & ((UINT16) ~0x20);
    }
    String++;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  IfrToString
//
// Description:   Evaluate opcode EFI_IFR_TO_STRING.
//
// Parameter:	  FormSet     - Formset which contains this opcode.
//  			  Format      - String format in EFI_IFR_TO_STRING.
//  			  Result      - Evaluation result for this opcode.
//
// Return value:  EFI_SUCCESS - Opcode evaluation success.
//		    	  Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrToString (
  IN EFI_HII_HANDLE		   *HiiHandle,
  IN UINT8                 Format,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String;
  CHAR16         *PrintFormat;
  CHAR16         Buffer[CHARACTER_NUMBER_FOR_VALUE];
  UINTN          BufferSize;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  switch (Value.Type) {
  case EFI_IFR_TYPE_NUM_SIZE_8:
  case EFI_IFR_TYPE_NUM_SIZE_16:
  case EFI_IFR_TYPE_NUM_SIZE_32:
  case EFI_IFR_TYPE_NUM_SIZE_64:
    BufferSize = CHARACTER_NUMBER_FOR_VALUE * sizeof (CHAR16);
    switch (Format) {
    case EFI_IFR_STRING_UNSIGNED_DEC:
    case EFI_IFR_STRING_SIGNED_DEC:
      PrintFormat = L"%ld";
      break;

    case EFI_IFR_STRING_LOWERCASE_HEX:
      PrintFormat = L"%lx";
      break;

    case EFI_IFR_STRING_UPPERCASE_HEX:
      PrintFormat = L"%lX";
      break;

    default:
      return EFI_UNSUPPORTED;
    }
    SPrint (Buffer, BufferSize, PrintFormat, Value.Value.u64);
    String = Buffer;
    break;

  case EFI_IFR_TYPE_STRING:
    EfiCopyMem (Result, &Value, sizeof (EFI_HII_VALUE));
    return EFI_SUCCESS;

  case EFI_IFR_TYPE_BOOLEAN:
    String = (Value.Value.b) ? L"True" : L"False";
    break;

  default:
    return EFI_UNSUPPORTED;
  }

  Result->Type = EFI_IFR_TYPE_STRING;
  Result->Value.string = NewString (String, HiiHandle);
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	 IfrToUint
//
// Description:  Evaluate opcode EFI_IFR_TO_UINT.
//
// Parameter:	 FormSet     - Formset which contains this opcode.
//				 Result      - Evaluation result for this opcode.
//
// Return value: EFI_SUCCESS - Opcode evaluation success.
//		    	 Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrToUint (
  IN EFI_HII_HANDLE		   *HiiHandle,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String;
  CHAR16         *StringPtr;
  UINTN          BufferSize;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Value.Type >= EFI_IFR_TYPE_OTHER) {
    return EFI_UNSUPPORTED;
  }

  Status = EFI_SUCCESS;
  if (Value.Type == EFI_IFR_TYPE_STRING) {
    String = GetToken (Value.Value.string, HiiHandle);
    if (String == NULL) {
      return EFI_NOT_FOUND;
    }

    IfrStrToUpper (String);
    StringPtr = EfiStrStr (String, L"0X");
    if (StringPtr != NULL) {
      //
      // Hex string
      //
      BufferSize = sizeof (UINT64);
      Status = HexStringToBuf ((UINT8 *) &Result->Value.u64, &BufferSize, StringPtr + 2, NULL);
    } else {
      //
      // BUGBUG: Need handle decimal string
      //
    }
    gBS->FreePool (String);
  } else {
    EfiCopyMem (Result, &Value, sizeof (EFI_HII_VALUE));
  }

  Result->Type = EFI_IFR_TYPE_NUM_SIZE_64;
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	 IfrCatenate
//
// Description:  Evaluate opcode EFI_IFR_TO_UINT.
//
// Parameter:	 FormSet     - Formset which contains this opcode.
//				 Result      - Evaluation result for this opcode.
//
// Return value: EFI_SUCCESS - Opcode evaluation success.
//		    	 Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrCatenate (
  IN EFI_HII_HANDLE		   *HiiHandle,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String[2];
  UINTN          Index;
  CHAR16         *StringPtr;

  //
  // String[0] - The second string
  // String[1] - The first string
  //
  String[0] = NULL;
  String[1] = NULL;
  StringPtr = NULL;
  Status = EFI_SUCCESS;

  for (Index = 0; Index < 2; Index++) {
    Status = PopExpression (&Value);
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if (Value.Type != EFI_IFR_TYPE_STRING) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }

    String[Index] = GetToken (Value.Value.string, HiiHandle);
    if (String== NULL) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }
  }

  StringPtr= EfiLibAllocatePool (EfiStrSize (String[1]) + EfiStrSize (String[0]));
  ASSERT (StringPtr != NULL);
  EfiStrCpy (StringPtr, String[1]);
  EfiStrCat (StringPtr, String[0]);

  Result->Type = EFI_IFR_TYPE_STRING;
  Result->Value.string = NewString (StringPtr, HiiHandle);

Done:
  EfiLibSafeFreePool (String[0]);
  EfiLibSafeFreePool (String[1]);
  EfiLibSafeFreePool (StringPtr);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	 IfrMatch
//
// Description:  Evaluate opcode EFI_IFR_MATCH.
//
// Parameter:	 FormSet     - Formset which contains this opcode.
//				 Result      - Evaluation result for this opcode.
//
// Return value: EFI_SUCCESS - Opcode evaluation success.
//		    	 Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrMatch (
  IN EFI_HII_HANDLE      *HiiHandle,
  OUT  EFI_HII_VALUE	 *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String[2];
  UINTN          Index;

  //
  // String[0] - The string to search
  // String[1] - pattern
  //
  String[0] = NULL;
  String[1] = NULL;
  Status = EFI_SUCCESS;
  for (Index = 0; Index < 2; Index++) {
    Status = PopExpression (&Value);
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if (Value.Type != EFI_IFR_TYPE_STRING) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }

    String[Index] = GetToken (Value.Value.string, HiiHandle);
    if (String== NULL) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }
  }

  Result->Type = EFI_IFR_TYPE_BOOLEAN;
  Result->Value.b = mUnicodeCollation->MetaiMatch (mUnicodeCollation, String[0], String[1]);

Done:
  EfiLibSafeFreePool (String[0]);
  EfiLibSafeFreePool (String[1]);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  IfrFind
//
// Description:   Evaluate opcode EFI_IFR_FIND.
//
// Parameter:	  FormSet     - Formset which contains this opcode.
// 				  Format      - Case sensitive or insensitive.
//  			  Result      - Evaluation result for this opcode.
//
// Return value:  EFI_SUCCESS - Opcode evaluation success.
//		    	  Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrFind (
  IN EFI_HII_HANDLE		   *HiiHandle,
  IN UINT8                 Format,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String[2];
  UINTN          Base;
  CHAR16         *StringPtr;
  UINTN          Index;

  if (Format > EFI_IFR_FF_CASE_INSENSITIVE) {
    return EFI_UNSUPPORTED;
  }

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type > EFI_IFR_TYPE_NUM_SIZE_64) {
    return EFI_UNSUPPORTED;
  }
  Base = (UINTN) Value.Value.u64;

  //
  // String[0] - sub-string
  // String[1] - The string to search
  //
  String[0] = NULL;
  String[1] = NULL;
  for (Index = 0; Index < 2; Index++) {
    Status = PopExpression (&Value);
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if (Value.Type != EFI_IFR_TYPE_STRING) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }

    String[Index] = GetToken (Value.Value.string, HiiHandle);
    if (String== NULL) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }

    if (Format == EFI_IFR_FF_CASE_INSENSITIVE) {
      //
      // Case insensitive, convert both string to upper case
      //
      IfrStrToUpper (String[Index]);
    }
  }

  Result->Type = EFI_IFR_TYPE_NUM_SIZE_64;
  if (Base >= EfiStrLen (String[1])) {
    Result->Value.u64 = 0xFFFFFFFFFFFFFFFF;
  } else {
    StringPtr = EfiStrStr (String[1] + Base, String[0]);
    Result->Value.u64 = (StringPtr == NULL) ? 0xFFFFFFFFFFFFFFFF : (StringPtr - String[1]);
  }

Done:
  EfiLibSafeFreePool (String[0]);
  EfiLibSafeFreePool (String[1]);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  IfrMid
//
// Description:   Evaluate opcode EFI_IFR_MID.
//
// Parameter:	  FormSet     - Formset which contains this opcode.
//				  Result      - Evaluation result for this opcode.
//
// Return value:  EFI_SUCCESS - Opcode evaluation success.
//		    	  Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrMid (
  IN EFI_HII_HANDLE		   *HiiHandle,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String;
  UINTN          Base;
  UINTN          Length;
  CHAR16         *SubString;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type > EFI_IFR_TYPE_NUM_SIZE_64) {
    return EFI_UNSUPPORTED;
  }
  Length = (UINTN) Value.Value.u64;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type > EFI_IFR_TYPE_NUM_SIZE_64) {
    return EFI_UNSUPPORTED;
  }
  Base = (UINTN) Value.Value.u64;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type != EFI_IFR_TYPE_STRING) {
    return EFI_UNSUPPORTED;
  }
  String = GetToken (Value.Value.string, HiiHandle);
  if (String == NULL) {
    return EFI_NOT_FOUND;
  }

  if (Length == 0 || Base >= EfiStrLen (String)) {
    SubString = gEmptyString;
  } else {
    SubString = String + Base;
    if ((Base + Length) < EfiStrLen (String)) {
      SubString[Length] = L'\0';
    }
  }

  Result->Type = EFI_IFR_TYPE_STRING;
  Result->Value.string = NewString (SubString, HiiHandle);

  gBS->FreePool (String);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  IfrToken
//
// Description:   Evaluate opcode EFI_IFR_TOKEN.
//
// Parameter:	  FormSet     - Formset which contains this opcode.
//				  Result      - Evaluation result for this opcode.
//
// Return value:  EFI_SUCCESS - Opcode evaluation success.
//		    	  Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrToken (
  IN EFI_HII_HANDLE		   *HiiHandle,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String[2];
  UINTN          Count;
  CHAR16         *Delimiter;
  CHAR16         *SubString;
  CHAR16         *StringPtr;
  UINTN          Index;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type > EFI_IFR_TYPE_NUM_SIZE_64) {
    return EFI_UNSUPPORTED;
  }
  Count = (UINTN) Value.Value.u64;

  //
  // String[0] - Delimiter
  // String[1] - The string to search
  //
  String[0] = NULL;
  String[1] = NULL;
  for (Index = 0; Index < 2; Index++) {
    Status = PopExpression (&Value);
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if (Value.Type != EFI_IFR_TYPE_STRING) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }

    String[Index] = GetToken (Value.Value.string, HiiHandle);
    if (String== NULL) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }
  }

  Delimiter = String[0];
  SubString = String[1];
  while (Count > 0) {
    SubString = EfiStrStr (SubString, Delimiter);
    if (SubString != NULL) {
      //
      // Skip over the delimiter
      //
      SubString = SubString + EfiStrLen (Delimiter);
    } else {
      break;
    }
    Count--;
  }

  if (SubString == NULL) {
    //
    // nth delimited sub-string not found, push an empty string
    //
    SubString = gEmptyString;
  } else {
    //
    // Put a NULL terminator for nth delimited sub-string
    //
    StringPtr = EfiStrStr (SubString, Delimiter);
    if (StringPtr != NULL) {
      *StringPtr = L'\0';
    }
  }

  Result->Type = EFI_IFR_TYPE_STRING;
  Result->Value.string = NewString (SubString, HiiHandle);

Done:
  EfiLibSafeFreePool (String[0]);
  EfiLibSafeFreePool (String[1]);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	   IfrSpan
//
// Description:    Evaluate opcode EFI_IFR_SPAN.
//
// Parameter:	   FormSet     - Formset which contains this opcode.
//                 Flags       - FIRST_MATCHING or FIRST_NON_MATCHING.
//                 Result      - Evaluation result for this opcode.
//
// Return value:   EFI_SUCCESS - Opcode evaluation success.
//		    	   Other       - Opcode evaluation failed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IfrSpan (
  IN EFI_HII_HANDLE		   *HiiHandle,
  IN UINT8                 Flags,
  OUT  EFI_HII_VALUE       *Result
  )
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String[2];
  CHAR16         *Charset;
  UINTN          Base;
  UINTN          Index;
  CHAR16         *StringPtr;
  BOOLEAN        Found;

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type > EFI_IFR_TYPE_NUM_SIZE_64) {
    return EFI_UNSUPPORTED;
  }
  Base = (UINTN) Value.Value.u64;

  //
  // String[0] - Charset
  // String[1] - The string to search
  //
  String[0] = NULL;
  String[1] = NULL;
  for (Index = 0; Index < 2; Index++) {
    Status = PopExpression (&Value);
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if (Value.Type != EFI_IFR_TYPE_STRING) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }

    String[Index] = GetToken (Value.Value.string, HiiHandle);
    if (String== NULL) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }
  }

  if (Base >= EfiStrLen (String[1])) {
    Status = EFI_UNSUPPORTED;
    goto Done;
  }

  Found = FALSE;
  StringPtr = String[1] + Base;
  Charset = String[0];
  while (*StringPtr != 0 && !Found) {
    Index = 0;
    while (Charset[Index] != 0) {
      if (*StringPtr >= Charset[Index] && *StringPtr <= Charset[Index + 1]) {
        if (Flags == EFI_IFR_FLAGS_FIRST_MATCHING) {
          Found = TRUE;
          break;
        }
      } else {
        if (Flags == EFI_IFR_FLAGS_FIRST_NON_MATCHING) {
          Found = TRUE;
          break;
        }
      }
      //
      // Skip characters pair representing low-end of a range and high-end of a range
      //
      Index += 2;
    }

    if (!Found) {
      StringPtr++;
    }
  }

  Result->Type = EFI_IFR_TYPE_NUM_SIZE_64;
  Result->Value.u64 = StringPtr - String[1];

Done:
  EfiLibSafeFreePool (String[0]);
  EfiLibSafeFreePool (String[1]);

  return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  ExtendValueToU64
//
// Description:   Zero extend integer/boolean/date/time to UINT64 for comparing.
//
// Parameter:	  Value    - HII Value to be converted.
//
// Return value:  None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ExtendValueToU64 (
  IN  EFI_HII_VALUE   *Value
  )
{
  UINT64  Temp;

  Temp = 0;
  switch (Value->Type) {
  case EFI_IFR_TYPE_NUM_SIZE_8:
    Temp = Value->Value.u8;
    break;

  case EFI_IFR_TYPE_NUM_SIZE_16:
    Temp = Value->Value.u16;
    break;

  case EFI_IFR_TYPE_NUM_SIZE_32:
    Temp = Value->Value.u32;
    break;

  case EFI_IFR_TYPE_BOOLEAN:
    Temp = Value->Value.b;
    break;

  case EFI_IFR_TYPE_TIME:
    Temp = Value->Value.u32 & 0xffffff;
    break;

  case EFI_IFR_TYPE_DATE:
    Temp = Value->Value.u32;
    break;

  default:
    return;
  }

  Value->Value.u64 = Temp;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	   CompareHiiValue
//
// Description:    Compare two Hii Value
//
// Parameter:	   Value1    - Expression value to compare on left-hand
//                 Value2    - Expression value to compare on right-hand
//                 HiiHandle - Only required for string compare
//
// Return value:    EFI_INVALID_PARAMETER  - Could not perform comparation on two values
// 				    0                      - Two operators equeal
//  				< 0                    - Value1 is greater than Value2
//  				> 0                    - Value1 is less than Value2
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN
CompareHiiValue (
  IN  EFI_HII_VALUE   *Value1,
  IN  EFI_HII_VALUE   *Value2,
  IN  EFI_HII_HANDLE  HiiHandle OPTIONAL
  )
{
  INTN    Result;
  INT64   Temp64;
  CHAR16  *Str1;
  CHAR16  *Str2;

  if (Value1->Type >= EFI_IFR_TYPE_OTHER || Value2->Type >= EFI_IFR_TYPE_OTHER ) {
    return EFI_INVALID_PARAMETER;
  }

  if (Value1->Type == EFI_IFR_TYPE_STRING || Value2->Type == EFI_IFR_TYPE_STRING ) {
    if (Value1->Type != Value2->Type) {
      //
      // Both Operator should be type of String
      //
      return EFI_INVALID_PARAMETER;
    }

    if (Value1->Value.string == 0 || Value2->Value.string == 0) {
      //
      // StringId 0 is reserved
      //
      return EFI_INVALID_PARAMETER;
    }

    if (Value1->Value.string == Value2->Value.string) {
      return 0;
    }

    Str1 = GetToken (Value1->Value.string, HiiHandle);
    if (Str1 == NULL) {
      //
      // String not found
      //
      return EFI_INVALID_PARAMETER;
    }

    Str2 = GetToken (Value2->Value.string, HiiHandle);
    if (Str2 == NULL) {
      gBS->FreePool (Str1);
      return EFI_INVALID_PARAMETER;
    }

    Result = EfiStrCmp (Str1, Str2);

    gBS->FreePool (Str1);
    gBS->FreePool (Str2);

    return Result;
  }

  //
  // Take remain types(integer, boolean, date/time) as integer
  //
  Temp64 = (INT64) (Value1->Value.u64 - Value2->Value.u64);
  if (Temp64 > 0) {
    Result = 1;
  } else if (Temp64 < 0) {
    Result = -1;
  } else {
    Result = 0;
  }

  return Result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	 _GetRuleControlfromId
//
// Description:
//
// Parameter:	 UINT8 *IFRData, CONTROL_INFO **RuleControl
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetRuleControlfromId(UINT16 RuleId, UINT16 PageId, CONTROL_INFO **RuleControl)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CONTROL_INFO *controlInfo = NULL;
  BOOLEAN found = FALSE;
  UINTN control = 0;

  PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[PageId]);
  if(pageInfo->PageHandle ==0)
  {
    Status = EFI_NOT_FOUND;
    goto DONE;
  }

  for(control= 0; (control < pageInfo->PageControls.ControlCount) && (found == FALSE); control++)
  {
    controlInfo = (CONTROL_INFO*)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);


    if(RuleId == controlInfo->ControlKey)
    {
      found = TRUE;
    }
  }

  if(found)
  {
    *RuleControl = controlInfo;
  }

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	 checkforpushthispresence
//
// Description: Checks the condition has EFI_IFR_THIS_OP
//
// Parameter:	 UINT8  *
//
// Return value: TRUE if EFI_IFR_THIS_OP presents else FALSE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN checkforpushthispresence (UINT8  *ControlConditionalPtr)
{
	EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER*)ControlConditionalPtr;
	UINTN 		inScope = 0;
	UINTN 		i = 0;
	
	if (opHeader->Scope)
	{
		do
		{
			switch (opHeader->OpCode)
			{
			case EFI_IFR_THIS_OP:
				return TRUE;
			case EFI_IFR_END_OP:
				inScope--;
				break;
			default:
				if(opHeader->Scope)
				{
					inScope++;
				}
			}
			i += opHeader->Length;
			opHeader = (EFI_IFR_OP_HEADER*)(ControlConditionalPtr + i);
		}while(inScope);
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------
//
// Procedure:	 GetValueFromParentControl
//
// Description: Gets the value for inconsistent/submitif from its parent control
//
// Parameter:	 UINT16, UINT16, EFI_HII_VALUE **, PAGE_INFO *, VOID *
//
// Return value: EFI_SUCCESS if value retrieved successfully else some other EFI Status
//-----------------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetValueFromQuestionId (UINT16 QuestionId, UINT16 PageId, EFI_HII_VALUE **Value);
EFI_STATUS GetValueFromParentControl (UINT16 QuestionId, UINT16 PageId, EFI_HII_VALUE **Value, PAGE_INFO *pageInfo, VOID *CtrlCondPtr)
{
	UINT32		Count = 1;
	UINTN			control = 0;
	EFI_STATUS 	Status = EFI_UNSUPPORTED;
	EFI_IFR_OP_HEADER *OpHeader;
	EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
	CHAR16 		*questionValue;
	EFI_STRING_ID  StrToken = 0;
	CONTROL_INFO *controlInfo;
	  
	for (control= 0; control < pageInfo->PageControls.ControlCount; control++)
	{
		controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);			//If two submit if present then questionid may be same so comparing conditionalptr also
		if ((QuestionId == controlInfo->ControlKey) && ((CONTROL_TYPE_MSGBOX == controlInfo->ControlType) || (NO_SUBMIT_IF == controlInfo->ControlType)) && (CtrlCondPtr == controlInfo->ControlConditionalPtr))
		{
			if (checkforpushthispresence (controlInfo->ControlConditionalPtr))
			{
				do					//Find the parent control. Inconsistent/submit only present inside question
				{
					controlInfo = (CONTROL_INFO*)((UINT8 *)(gControlInfo) + pageInfo->PageControls.ControlList [control-Count]);
					Count ++;
				}while ((CONTROL_TYPE_MSGBOX == controlInfo->ControlType) || (NO_SUBMIT_IF == controlInfo->ControlType));		//find parent suppress all the inconsistent/submit present in the control
				OpHeader=(EFI_IFR_OP_HEADER *)controlInfo->ControlPtr;
				  if (EFI_IFR_STRING_OP != OpHeader->OpCode)
				  {
					  Status = _GetValueFromQuestionId (controlInfo->ControlKey, PageId, Value);
				  }
				  else
				  {
					UINTN dataWidth = UefiGetWidth (controlInfo->ControlPtr);
					questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8 *)controlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));
					questionValue = EfiLibAllocateZeroPool (dataWidth + sizeof (CHAR16));		//sizeof (CHAR16) is for NULL if maximum characters used.
					 if (NULL == questionValue)
					 {
						 return EFI_OUT_OF_RESOURCES;
					 }
					
					// EIP-42300: Updated the dataWidth in comparison to the maximum supported
					Status = VarGetValue (controlInfo->ControlVariable, questionHdr->VarStoreInfo.VarOffset, dataWidth, (VOID *)questionValue);
					if (!EFI_ERROR(Status))
					{
						if (*questionValue != 0)
						{
							StrToken = HiiAddString (controlInfo->ControlHandle, questionValue);
							(*Value)->Value.string = StrToken;
							(*Value)->Type = EFI_IFR_TYPE_STRING;
						}
						else
						{
							Status = EFI_NOT_STARTED;			//If null string then dont compare
						}
					}
				  }
			}
			break;
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	 _GetValueFromQuestionId
//
// Description:
//
// Parameter:	 UINT16 QuestionId, UINT16 PageId, UINT64 *Value
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetValueFromQuestionId(UINT16 QuestionId, UINT16 PageId, EFI_HII_VALUE **Value)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
  BOOLEAN found = FALSE;
  UINT32 varId = 0;
  UINTN control = 0;
  UINT64 questionValue = 0;

  CONTROL_INFO *controlInfo = NULL;

  PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[PageId]);

  if(pageInfo->PageHandle ==0)
  {
    Status = EFI_NOT_FOUND;
    goto DONE;
  }

  for ( control= 0; (control < pageInfo->PageControls.ControlCount) && (found == FALSE); control++ )
  {
    controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

    if(QuestionId == controlInfo->ControlKey)
    {
	    if ((CONTROL_TYPE_MSGBOX == controlInfo->ControlType) || (NO_SUBMIT_IF == controlInfo->ControlType) || gInconsistCondPtr)
	    {
		    if (gInconsistCondPtr == controlInfo->ControlConditionalPtr)		//All inconsistentif will have 0 as question id so adding more check
		    {
			  varId = controlInfo->ControlVariable;
			  found = TRUE;			    
		    }
	    }
	    else
	    {
		  varId = controlInfo->ControlVariable;
		  found = TRUE;
	    }
    }
  }

  if(!found)
  {
    // Control Definition not in this Page. Look within the formset
    EFI_HII_HANDLE pgHandle = pageInfo->PageHandle;
    UINT32 page = 0;

    for(;page < gPages->PageCount && (found == FALSE); page++)
    {
/*
      if(page == PageId)
      {
        continue;
      }
*/
      pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);
      if(pageInfo->PageHandle != pgHandle)
      {
        continue;
      }

      for(control = 0; control < pageInfo->PageControls.ControlCount && (found == FALSE); control++)
      {
        controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

        if(QuestionId == controlInfo->ControlKey)
        {
          varId = controlInfo->ControlVariable;
          found = TRUE;
        }
      }
    }
  }

	if(found)
	{
		if (NULL != controlInfo->ControlPtr)      //For inconsistent and nosubmitif controlptr will be NULL
		{
			UINTN dataWidth = UefiGetWidth(controlInfo->ControlPtr);
			questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8 *)controlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));
			
			// EIP-42300: Updated the dataWidth in comparision to the maximum supported
			Status = VarGetValue(varId, questionHdr->VarStoreInfo.VarOffset, (( dataWidth > sizeof(UINT64))? sizeof(UINT64) : dataWidth ), &questionValue);
			if(EFI_ERROR(Status))
			{
				goto DONE;
			}
			(*Value)->Value.u64 = questionValue;
		}
		else if ((CONTROL_TYPE_MSGBOX == controlInfo->ControlType) || (NO_SUBMIT_IF == controlInfo->ControlType))		//Check for inconistent control
		{
			Status = GetValueFromParentControl (QuestionId, PageId, Value, pageInfo, controlInfo->ControlConditionalPtr);
		}
	}
DONE:
  return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	 _SetValueFromQuestionId
//
// Description:
//
// Parameter:	 UINT16 QuestionId, UINT16 PageId, UINT64 *Value
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _SetValueFromQuestionId(UINT16 QuestionId, UINT16 PageId, EFI_HII_VALUE *Value)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
  BOOLEAN found = FALSE;
  UINT32 varId = 0;
  UINTN control = 0;
  UINT64 questionValue = Value->Value.u64;

  CONTROL_INFO *controlInfo = NULL;

  PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[PageId]);

  if(pageInfo->PageHandle ==0)
  {
    Status = EFI_NOT_FOUND;
    goto DONE;
  }

  for ( control= 0; (control < pageInfo->PageControls.ControlCount) && (found == FALSE); control++ )
  {
    controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

    if(QuestionId == controlInfo->ControlKey)
    {
      varId = controlInfo->ControlVariable;
      found = TRUE;
    }
  }

  if(!found)
  {
    // Control Definition not in this Page. Look within the formset
    EFI_HII_HANDLE pgHandle = pageInfo->PageHandle;
    UINT32 page = 0;

    for(;page < gPages->PageCount && (found == FALSE); page++)
    {

      pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);
      if(pageInfo->PageHandle != pgHandle)
      {
        continue;
      }

      for(control = 0; control < pageInfo->PageControls.ControlCount && (found == FALSE); control++)
      {
        controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

        if(QuestionId == controlInfo->ControlKey)
        {
          varId = controlInfo->ControlVariable;
          found = TRUE;
        }
      }
    }
  }

  if(found)
  {
    UINTN dataWidth = UefiGetWidth(controlInfo->ControlPtr);
    questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8 *)controlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));

	// EIP-42300: Updated the dataWidth in comparision to the maximum supported
	Status = VarSetValue(varId, questionHdr->VarStoreInfo.VarOffset, (( dataWidth > sizeof(UINT64))? sizeof(UINT64) : dataWidth ), &questionValue);
    
  }

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	 IsScopeStackEmpty
//
// Description:
//
// Parameter:	 VOID
//
// Return value: BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsScopeStackEmpty()
{
  UINT8 opCode = 0;
  EFI_STATUS status = EFI_SUCCESS;

  status = PopScope(&opCode);
  if(status == EFI_ACCESS_DENIED)
  {
    return TRUE;
  }

  status = PushScope(opCode);

  return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetPageIdFromGuid
//
// Description: Finds the page ID with matching Guid from the page list
//
// Input:	EFI_GUID *FormSetGuid
//          UINT16 *PageID
//
// Output:	EFI_STATUS status - EFI_SUCCESS, if successful,
//                              EFI_INVALID_PARAMETER, if invalid values found
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetpageIdFromGuid(EFI_GUID *FormGuid, UINT16 *PageID)
{
  EFI_STATUS status = EFI_INVALID_PARAMETER;
  UINT32 pgIndex = 0; 
  PAGE_INFO *pgInfo = (PAGE_INFO *)NULL;
  PAGE_ID_INFO *pageIdInfo = (PAGE_ID_INFO*)NULL;
  
 
  if(gPages && gApplicationData && gPageIdList)
  {
    for(pgIndex = 0; pgIndex < gPages->PageCount; pgIndex++)
    {
      pgInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[pgIndex]);
      if(pgInfo){
        pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[pgInfo->PageIdIndex]);
        if(pageIdInfo && (EfiCompareGuid(FormGuid, &(pageIdInfo->PageGuid)) == TRUE))//Compare Guid
        {
          *PageID  = pgInfo->PageID;
          status = EFI_SUCCESS;
		  goto DONE;
        }
      }
     }
   }

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	 EvaluateExpression
//
// Description:  Evaluate the result of a HII expression
//
// Parameter:	 IN CONTROL_INFO *ControlInfo,
//               IN OUT BOOLEAN  *ExpressionResult,
//               OUT UINTN       *Offset
//
// Return value: EFI_SUCCESS           - The expression evaluated successfuly
//               EFI_NOT_FOUND         - The Question which referenced by a
//                                       QuestionId could not be found.
//               EFI_OUT_OF_RESOURCES  - There is not enough system memory to
//                                       grow the stack.
//               EFI_ACCESS_DENIED     - The pop operation underflowed the stack
//               EFI_INVALID_PARAMETER - Syntax error with the Expression
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EvaluateExpression (
  IN CONTROL_INFO *ControlInfo,
  IN OUT EFI_HII_VALUE   *ExpressionResult,
  OUT UINTN *Offset
  )
{
  EFI_IFR_OP_HEADER		  *ifrData = NULL;
  CONTROL_INFO			  *ruleControl = NULL;
  EFI_STATUS              Status;
  UINT16                  Index;
  EFI_HII_VALUE           Data1;
  EFI_HII_VALUE           Data2;
  EFI_HII_VALUE           Data3;
  EFI_HII_VALUE			  *questionValue = NULL;
  EFI_HII_VALUE			  *questionValue2 = NULL;
  EFI_HII_VALUE           *Value = NULL;
  EFI_QUESTION_ID		      questionId = 0;
  INTN                    Result;
  CHAR16                  *StrPtr = NULL;
  UINTN        i = 0;
  UINT8        opCode = 0;
  BOOLEAN      IsDevicePathFound = FALSE ,GUIDFound = FALSE;
  EFI_GUID     formSetGuid = {0}, zeroFormSetGuid = {0};
  UINTN        count = 0,tempcount = 0;
  CHAR16       *devPathStr = (CHAR16 *)NULL, *tempDevPathStr = (CHAR16 *)NULL;
  EFI_DEVICE_PATH_PROTOCOL *tempDevPath = (EFI_DEVICE_PATH_PROTOCOL *)NULL;
  UINT16       DevicePath = 0;
  //
  // Always reset the stack before evaluating an Expression
  //
  ResetExpressionStack ();

  ExpressionResult->Type = EFI_IFR_TYPE_OTHER;

  opCode = ((EFI_IFR_OP_HEADER*)ControlInfo->ControlConditionalPtr)->OpCode;
  if(opCode != EFI_IFR_SUPPRESS_IF_OP && opCode != EFI_IFR_NO_SUBMIT_IF_OP &&
    opCode != EFI_IFR_INCONSISTENT_IF_OP && opCode != EFI_IFR_GRAY_OUT_IF_OP &&
    opCode != EFI_IFR_DISABLE_IF_OP && opCode != EFI_IFR_VALUE_OP)
  {
    Status = EFI_SUCCESS;
    goto DONE;
  }

  questionValue = (EFI_HII_VALUE*)EfiLibAllocateZeroPool(sizeof(EFI_HII_VALUE));
  if(questionValue == NULL)
  {
    Status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  questionValue2 = (EFI_HII_VALUE*)EfiLibAllocateZeroPool(sizeof(EFI_HII_VALUE));
  if(questionValue2 == NULL)
  {
    Status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  if(((EFI_IFR_OP_HEADER*)ControlInfo->ControlConditionalPtr)->OpCode == EFI_IFR_RULE_OP)
  {
    PushScope(EFI_IFR_RULE_OP);
  }else
  {
    PushScope(((EFI_IFR_OP_HEADER*)ControlInfo->ControlConditionalPtr)->OpCode);
    if (
		    ( ( (EFI_IFR_OP_HEADER*)ControlInfo->ControlConditionalPtr)->OpCode == EFI_IFR_INCONSISTENT_IF_OP) || 
		    ( ( (EFI_IFR_OP_HEADER*)ControlInfo->ControlConditionalPtr)->OpCode == EFI_IFR_NO_SUBMIT_IF_OP)
	 )
    {
	    gInconsistCondPtr = ControlInfo->ControlConditionalPtr;
    }
  }

  i += ((EFI_IFR_OP_HEADER*)ControlInfo->ControlConditionalPtr)->Length;

  while (IsScopeStackEmpty() == FALSE)
  {
    ifrData = (EFI_IFR_OP_HEADER*)((UINT8 *)ControlInfo->ControlConditionalPtr + i);

    EfiZeroMem (&Data1, sizeof (EFI_HII_VALUE));
    EfiZeroMem (&Data2, sizeof (EFI_HII_VALUE));
    EfiZeroMem (&Data3, sizeof (EFI_HII_VALUE));
    EfiZeroMem (questionValue, sizeof(EFI_HII_VALUE));
    EfiZeroMem (questionValue2, sizeof(EFI_HII_VALUE));

    Value = &Data3;
    Value->Type = EFI_IFR_TYPE_BOOLEAN;
    Status = EFI_SUCCESS;

    questionValue->Type = EFI_IFR_TYPE_NUM_SIZE_64;

    switch (ifrData->OpCode)
    {
      //
      // Built-in functions
      //
    case EFI_IFR_EQ_ID_VAL_OP:
      questionId = ((EFI_IFR_EQ_ID_VAL*)ifrData)->QuestionId;
      Status = _GetValueFromQuestionId(questionId, ControlInfo->ControlPageID, &questionValue);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }

      questionValue2->Type = EFI_IFR_TYPE_NUM_SIZE_64;
      questionValue2->Value.u64 = ((EFI_IFR_EQ_ID_VAL*)ifrData)->Value;

      Result = CompareHiiValue (questionValue, questionValue2, NULL);
      if (Result == EFI_INVALID_PARAMETER)
      {
        Status = EFI_INVALID_PARAMETER;
	goto DONE;
      }
      Value->Value.b = (Result == 0) ? TRUE : FALSE;
      break;

    case EFI_IFR_EQ_ID_ID_OP:
      questionId = ((EFI_IFR_EQ_ID_ID*)ifrData)->QuestionId1;
      Status = _GetValueFromQuestionId(questionId, ControlInfo->ControlPageID, &questionValue);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }
      questionId = ((EFI_IFR_EQ_ID_ID*)ifrData)->QuestionId2;
      Status = _GetValueFromQuestionId(questionId, ControlInfo->ControlPageID, &questionValue2);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }

      Result = CompareHiiValue (questionValue, questionValue2, ControlInfo->ControlHandle);
      if (Result == EFI_INVALID_PARAMETER)
      {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }
      Value->Value.b = (Result == 0) ? TRUE : FALSE;
      break;

    case EFI_IFR_EQ_ID_LIST_OP:
      questionId = ((EFI_IFR_EQ_ID_LIST*)ifrData)->QuestionId;
      Status = _GetValueFromQuestionId(questionId, ControlInfo->ControlPageID, &questionValue);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }

      Value->Value.b = FALSE;
      for (Index =0; Index < ((EFI_IFR_EQ_ID_LIST*)ifrData)->ListLength; Index++)
      {
        if (questionValue->Value.u16 == ((EFI_IFR_EQ_ID_LIST*)ifrData)->ValueList[Index])
        {
          Value->Value.b = TRUE;
          break;
        }
      }
      break;

    case EFI_IFR_DUP_OP:
      Status = PopExpression (Value);
      if (EFI_ERROR (Status))
      {
        goto DONE;
      }

      Status = PushExpression (Value);
      break;

    case EFI_IFR_QUESTION_REF1_OP:
    case EFI_IFR_THIS_OP:
      if(ifrData->OpCode == EFI_IFR_THIS_OP)
      {
        questionId = ControlInfo->ControlKey;
      }else
      {
        questionId = ((EFI_IFR_QUESTION_REF1*)ifrData)->QuestionId;
      }
      Status = _GetValueFromQuestionId(questionId, ControlInfo->ControlPageID, &questionValue);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }

      Value = questionValue;
      break;

     
     case EFI_IFR_QUESTION_REF3_OP:

      //
      // EFI_IFR_QUESTION_REF3
      // Pop an expression from the expression stack
      //
      Status = PopExpression (Value);
      if (EFI_ERROR (Status))
      {
         goto DONE;
      }
      
      //
      // Validate the expression value
      //
      
      if ((Value->Type > EFI_IFR_TYPE_NUM_SIZE_64) || (Value->Value.u64 > 0xffff))
      {
         Status = EFI_NOT_FOUND;
         goto DONE;
      }
      
      if(ifrData->Length > sizeof(EFI_IFR_QUESTION_REF3))
      {
         if(ifrData->Length > sizeof(EFI_IFR_QUESTION_REF3_2))
         {
            MemCopy(&formSetGuid,&((EFI_IFR_QUESTION_REF3_3*)ifrData)->Guid, sizeof (EFI_GUID));
            if(EfiCompareGuid(&formSetGuid, &zeroFormSetGuid) == FALSE)
            {
               UINT16 PageID;
               Status = GetpageIdFromGuid(&formSetGuid,&PageID);
               if(Status == 0)
               {
                  GUIDFound = TRUE;
                  Status = _GetValueFromQuestionId(Value->Value.u16,PageID, &questionValue);
                  if(EFI_ERROR(Status))
                  {
                     goto DONE;
                  }
               }
            }
         }
         DevicePath = ifrData->Length < sizeof(EFI_IFR_QUESTION_REF3_3) ? ((EFI_IFR_QUESTION_REF3_2*)ifrData)->DevicePath : ((EFI_IFR_QUESTION_REF3_3*)ifrData)->DevicePath;
         if(DevicePath != 0 && !GUIDFound)
         {
            PAGE_INFO *tempPageInfo1 = NULL;
            devPathStr = GetToken (DevicePath,ControlInfo->ControlHandle);               
            
            if(devPathStr == NULL){
               goto DONE;
            }
         
            for(count = 0; count < gPages->PageCount; count++)
            {
               PAGE_INFO *tempPageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[count]);
               if(tempPageInfo == NULL)
               {
                  continue;
               }
               Status = GetDevPathFromHandle(tempPageInfo->PageHandle, &tempDevPath);
               if((Status == EFI_SUCCESS) && (tempDevPath != NULL) && tempPageInfo->PageParentID == 0)
               {
                  GetStringFromDevPath(tempDevPath, &tempDevPathStr);
                  if(EfiStrCmp(devPathStr, tempDevPathStr) == 0)
                  {
                     tempcount++;
                     tempPageInfo1=tempPageInfo;
                  }
                     MemFreePointer( (VOID **)&tempDevPathStr );
               }
            }
            MemFreePointer( (VOID **)&devPathStr );
                  
            if(tempcount == 1){
               IsDevicePathFound = TRUE;
               Status = _GetValueFromQuestionId(Value->Value.u16, tempPageInfo1->PageID, &questionValue);
               if(EFI_ERROR(Status))
               {
                  goto DONE;
               }
            }   
            if(tempcount > 1){
               goto DONE;
            }
         }
      }
      if(!IsDevicePathFound && !GUIDFound && !tempcount) 
      {
         Status = _GetValueFromQuestionId(Value->Value.u16, ControlInfo->ControlPageID, &questionValue);
         if(EFI_ERROR(Status))
         {
            goto DONE;
         }
      }
      Value = questionValue;
      break;

    case EFI_IFR_RULE_REF_OP:
      questionId = ((EFI_IFR_RULE_REF*)ifrData)->RuleId;

      Status = _GetRuleControlfromId(questionId, ControlInfo->ControlPageID, &ruleControl);

      /* This Section Needs to be modified
      //
      // Find expression for this rule
      //
      RuleExpression = RuleIdToExpression (Form, OpCode->RuleId);
      if (RuleExpression == NULL) {
      return EFI_NOT_FOUND;
      }*/

      //
      // Evaluate this rule expression
      //
      Status = EvaluateExpression (ruleControl, ExpressionResult, Offset);
      if (EFI_ERROR (Status))
      {
		goto DONE;
      }

      Value = ExpressionResult;
      break;

    case EFI_IFR_STRING_REF1_OP:
      Value->Type = EFI_IFR_TYPE_STRING;
      Value->Value.string = ((EFI_IFR_STRING_REF1*)ifrData)->StringId;
      break;

      //
      // Constant
      //
    case EFI_IFR_TRUE_OP:
      Value->Value.b = TRUE;
      break;
    case EFI_IFR_FALSE_OP:
      Value->Value.b = FALSE;
      break;
    case EFI_IFR_ONE_OP:
#define ONE 1
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_8;
      Value->Value.u8 = ONE;
      break;
    case EFI_IFR_ONES_OP:
#define ONES 0xFFFFFFFFFFFFFFFF
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;
      Value->Value.u64 = ONES;
      break;
    case EFI_IFR_UINT8_OP:
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_8;
      Value->Value.u8 = ((EFI_IFR_UINT8*)ifrData)->Value;
      break;
    case EFI_IFR_UINT16_OP:
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_16;
      Value->Value.u16 = ((EFI_IFR_UINT16*)ifrData)->Value;
      break;
    case EFI_IFR_UINT32_OP:
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_32;
      Value->Value.u32 = ((EFI_IFR_UINT32*)ifrData)->Value;
      break;
    case EFI_IFR_UINT64_OP:
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;
      Value->Value.u64 = ((EFI_IFR_UINT64*)ifrData)->Value;
      break;
    case EFI_IFR_UNDEFINED_OP:
      Value->Type = EFI_IFR_TYPE_OTHER;
      break;
    case EFI_IFR_VERSION_OP:
#define VERSION (UINT16)(2<<8)|((3<<4) | 0x1) //EIP:56355 Updated the Version to 2.3.1
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_16;
      Value->Value.u16 = VERSION;
      break;
    case EFI_IFR_ZERO_OP:
#define ZERO 0
      Value->Type = EFI_IFR_TYPE_NUM_SIZE_8;
      Value->Value.u8 = ZERO;
      break;

      //
      // unary-op
      //
    case EFI_IFR_LENGTH_OP:
      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
		goto DONE;
      }
      if (Value->Type != EFI_IFR_TYPE_STRING) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      StrPtr = GetToken (Value->Value.string, ControlInfo->ControlHandle);
      if (StrPtr == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;
      Value->Value.u64 = EfiStrLen (StrPtr);
      gBS->FreePool (StrPtr);
      break;

    case EFI_IFR_NOT_OP:
      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Value->Type != EFI_IFR_TYPE_BOOLEAN) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }
      Value->Value.b = !Value->Value.b;
      break;

    case EFI_IFR_QUESTION_REF2_OP:
      //
      // Pop an expression from the expression stack
      //
      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Validate the expression value
      //
      if ((Value->Type > EFI_IFR_TYPE_NUM_SIZE_64) || (Value->Value.u64 > 0xffff)) {
        Status = EFI_NOT_FOUND;
        goto DONE;
      }

      Status = _GetValueFromQuestionId(Value->Value.u16, ControlInfo->ControlPageID, &questionValue);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }

      Value = questionValue;
      break;

    case EFI_IFR_STRING_REF2_OP:
      //
      // Pop an expression from the expression stack
      //
      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Validate the expression value
      //
      if ((Value->Type > EFI_IFR_TYPE_NUM_SIZE_64) || (Value->Value.u64 > 0xffff)) {
        Status = EFI_NOT_FOUND;
        goto DONE;
      }

      Value->Type = EFI_IFR_TYPE_STRING;
      StrPtr = GetToken (Value->Value.u16, ControlInfo->ControlHandle);
      if (StrPtr == NULL) {
        //
        // If String not exit, push an empty string
        //
        Value->Value.string = NewString (gEmptyString, ControlInfo->ControlHandle);
      } else {
        Index = (UINT16) Value->Value.u64;
        Value->Value.string = Index;
        gBS->FreePool (StrPtr);
      }
      break;

    case EFI_IFR_TO_BOOLEAN_OP:
      //
      // Pop an expression from the expression stack
      //
      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Convert an expression to a Boolean
      //
      if (Value->Type <= EFI_IFR_TYPE_DATE) {
        //
        // When converting from an unsigned integer, zero will be converted to
        // FALSE and any other value will be converted to TRUE.
        //
        Value->Value.b = (Value->Value.u64) ? TRUE : FALSE;

        Value->Type = EFI_IFR_TYPE_BOOLEAN;
      } else if (Value->Type == EFI_IFR_TYPE_STRING) {
        //
        // When converting from a string, if case-insensitive compare
        // with "true" is True, then push True. If a case-insensitive compare
        // with "false" is True, then push False.
        //
        StrPtr = GetToken (Value->Value.string, ControlInfo->ControlHandle);
        if (StrPtr == NULL) {
          Status = EFI_INVALID_PARAMETER;
          goto DONE;
        }

        if ((EfiStrCmp (StrPtr, L"true") == 0))
        {
          Value->Value.b = TRUE;
        } else if(EfiStrCmp (StrPtr, L"false") == 0)
        {
          Value->Value.b = FALSE;
        } else
        {
          Value->Type = EFI_IFR_TYPE_OTHER;
        }
        gBS->FreePool (StrPtr);
        Value->Type = EFI_IFR_TYPE_BOOLEAN;
      }
      break;

    case EFI_IFR_TO_STRING_OP:
      Status = IfrToString (ControlInfo->ControlHandle, ((EFI_IFR_TO_STRING*)ifrData)->Format, Value);
      break;

    case EFI_IFR_TO_UINT_OP:
      Status = IfrToUint (ControlInfo->ControlHandle, Value);
      break;

    case EFI_IFR_TO_LOWER_OP:
    case EFI_IFR_TO_UPPER_OP:
      Status = InitializeUnicodeCollationProtocol ();
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      if (Value->Type != EFI_IFR_TYPE_STRING) {
        Status = EFI_UNSUPPORTED;
        goto DONE;
      }

      StrPtr = GetToken (Value->Value.string, ControlInfo->ControlHandle);
      if (StrPtr == NULL) {
        Status = EFI_NOT_FOUND;
        goto DONE;
      }

      if (ifrData->OpCode == EFI_IFR_TO_LOWER_OP) {
        mUnicodeCollation->StrLwr (mUnicodeCollation, StrPtr);
      } else {
        mUnicodeCollation->StrUpr (mUnicodeCollation, StrPtr);
      }
      Value->Value.string = NewString (StrPtr, ControlInfo->ControlHandle);
      gBS->FreePool (StrPtr);
      break;

    case EFI_IFR_BITWISE_NOT_OP:
      //
      // Pop an expression from the expression stack
      //
      Status = PopExpression (Value);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Value->Type > EFI_IFR_TYPE_DATE) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;
      Value->Value.u64 = ~Value->Value.u64;
      break;

    //
    // binary-op
    //
    case EFI_IFR_ADD_OP:
    case EFI_IFR_SUBTRACT_OP:
    case EFI_IFR_MULTIPLY_OP:
    case EFI_IFR_DIVIDE_OP:
    case EFI_IFR_MODULO_OP:
    case EFI_IFR_BITWISE_AND_OP:
    case EFI_IFR_BITWISE_OR_OP:
    case EFI_IFR_SHIFT_LEFT_OP:
    case EFI_IFR_SHIFT_RIGHT_OP:
      //
      // Pop an expression from the expression stack
      //
      Status = PopExpression (&Data2);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Data2.Type > EFI_IFR_TYPE_DATE) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      //
      // Pop another expression from the expression stack
      //
      Status = PopExpression (&Data1);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Data1.Type > EFI_IFR_TYPE_DATE) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;

      switch (ifrData->OpCode) {
        case EFI_IFR_ADD_OP:
          Value->Value.u64 = Data1.Value.u64 + Data2.Value.u64;
          break;

        case EFI_IFR_SUBTRACT_OP:
          Value->Value.u64 = Data1.Value.u64 - Data2.Value.u64;
          break;

        case EFI_IFR_MULTIPLY_OP:
          Value->Value.u64 = MultU64x32 (Data1.Value.u64, (UINT32)Data2.Value.u64);
          break;

        case EFI_IFR_DIVIDE_OP:
          Value->Value.u64 = AmiTseDivU64x32 (Data1.Value.u64, (UINT32)Data2.Value.u64,NULL);
          break;

        case EFI_IFR_MODULO_OP:
          Value->Value.u64 = 0;
          AmiTseDivU64x32(Data1.Value.u64, (UINT32)Data2.Value.u64, (UINTN*)&Value->Value.u64);
          break;

        case EFI_IFR_BITWISE_AND_OP:
          Value->Value.u64 = Data1.Value.u64 & Data2.Value.u64;
          break;

        case EFI_IFR_BITWISE_OR_OP:
          Value->Value.u64 = Data1.Value.u64 | Data2.Value.u64;
          break;

        case EFI_IFR_SHIFT_LEFT_OP:
          Value->Value.u64 = LShiftU64 (Data1.Value.u64, (UINTN) Data2.Value.u64);
          break;

        case EFI_IFR_SHIFT_RIGHT_OP:
          Value->Value.u64 = RShiftU64 (Data1.Value.u64, (UINTN) Data2.Value.u64);
          break;

        default:
          break;
      }
      break;

    case EFI_IFR_AND_OP:
    case EFI_IFR_OR_OP:
      //
      // Two Boolean operator
      //
      Status = PopExpression (&Data2);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Data2.Type != EFI_IFR_TYPE_BOOLEAN) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      //
      // Pop another expression from the expression stack
      //
      Status = PopExpression (&Data1);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Data1.Type != EFI_IFR_TYPE_BOOLEAN) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      if (ifrData->OpCode == EFI_IFR_AND_OP) {
        Value->Value.b = Data1.Value.b && Data2.Value.b;
      } else {
        Value->Value.b = Data1.Value.b || Data2.Value.b;
      }
      break;

    case EFI_IFR_EQUAL_OP:
    case EFI_IFR_NOT_EQUAL_OP:
    case EFI_IFR_GREATER_EQUAL_OP:
    case EFI_IFR_GREATER_THAN_OP:
    case EFI_IFR_LESS_EQUAL_OP:
    case EFI_IFR_LESS_THAN_OP:
      //
      // Compare two integer, string, boolean or date/time
      //
      Status = PopExpression (&Data2);
      if (EFI_ERROR (Status)) {
	goto DONE;
      }
      if (Data2.Type > EFI_IFR_TYPE_BOOLEAN && Data2.Type != EFI_IFR_TYPE_STRING) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      //
      // Pop another expression from the expression stack
      //
      Status = PopExpression (&Data1);
      if (EFI_ERROR (Status)) {
	goto DONE;
      }

      Result = CompareHiiValue (&Data1, &Data2, ControlInfo->ControlHandle);
      if (Result == EFI_INVALID_PARAMETER) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      switch (ifrData->OpCode) {
      case EFI_IFR_EQUAL_OP:
        Value->Value.b = (Result == 0) ? TRUE : FALSE;
        break;

      case EFI_IFR_NOT_EQUAL_OP:
        Value->Value.b = (Result != 0) ? TRUE : FALSE;
        break;

      case EFI_IFR_GREATER_EQUAL_OP:
        Value->Value.b = (Result >= 0) ? TRUE : FALSE;
        break;

      case EFI_IFR_GREATER_THAN_OP:
        Value->Value.b = (Result > 0) ? TRUE : FALSE;
        break;

      case EFI_IFR_LESS_EQUAL_OP:
        Value->Value.b = (Result <= 0) ? TRUE : FALSE;
        break;

      case EFI_IFR_LESS_THAN_OP:
        Value->Value.b = (Result < 0) ? TRUE : FALSE;
        break;

      default:
        break;
      }
      break;

    case EFI_IFR_MATCH_OP:
      Status = IfrMatch (ControlInfo->ControlHandle, Value);
      break;

    case EFI_IFR_CATENATE_OP:
      Status = IfrCatenate (ControlInfo->ControlHandle, Value);
      break;

    //
    // ternary-op
    //
    case EFI_IFR_CONDITIONAL_OP:
      //
      // Pop third expression from the expression stack
      //
      Status = PopExpression (&Data3);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Pop second expression from the expression stack
      //
      Status = PopExpression (&Data2);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Pop first expression from the expression stack
      //
      Status = PopExpression (&Data1);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
      if (Data1.Type != EFI_IFR_TYPE_BOOLEAN) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      if (Data1.Value.b) {
        Value = &Data3;
      } else {
        Value = &Data2;
      }
      break;

    case EFI_IFR_FIND_OP:
      Status = IfrFind (ControlInfo->ControlHandle, ((EFI_IFR_FIND*)ifrData)->Format, Value);
      break;

    case EFI_IFR_MID_OP:
      Status = IfrMid (ControlInfo->ControlHandle, Value);
      break;

    case EFI_IFR_TOKEN_OP:
      Status = IfrToken (ControlInfo->ControlHandle, Value);
      break;

    case EFI_IFR_SPAN_OP:
      Status = IfrSpan (ControlInfo->ControlHandle, ((EFI_IFR_SPAN*)ifrData)->Flags, Value);
      break;

    default:
      Status = PopScope(&opCode);
      if (EFI_ERROR (Status))
      {
        goto DONE;
      }
      continue;
    }
    if (EFI_ERROR (Status))
    {
	  goto DONE;
    }

    Status = PushExpression (Value);
    if (EFI_ERROR (Status))
    {
      goto DONE;
    }

    i += ifrData->Length;
  }
	if (NULL != ifrData)//EIP-75384 Static code
	{
		if(ifrData->OpCode == EFI_IFR_END_OP)
			i += ifrData->Length;
	}

  //
  // Pop the final result from expression stack
  //
  Value = &Data1;
  Status = PopExpression (Value);
  if (EFI_ERROR (Status)) {
    goto DONE;
  }

  //
  // After evaluating an expression, there should be only one value left on the expression stack
  //
  if (PopExpression (Value) != EFI_ACCESS_DENIED)
  {
    Status = EFI_INVALID_PARAMETER;
    goto DONE;
  }

  EfiCopyMem (ExpressionResult, Value, sizeof (EFI_HII_VALUE));

DONE:
  MemFreePointer(&questionValue);
  MemFreePointer(&questionValue2);

  *Offset = i;
  gInconsistCondPtr = NULL;
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  _SkipExpression
//
// Description:   Travels till the end of the current Expression and returns the offset
//
// Parameter:	  ControlCondPtr - Pointer to the Expression beginning.
//
// Return value:  UINTN  - Offsets to skip the current expression.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _SkipExpression(UINT8 *ControlCondPtr)
{
  EFI_IFR_OP_HEADER *OpHeader = ( EFI_IFR_OP_HEADER * )ControlCondPtr;
  UINTN offset = 0;
  INTN inScope = 0;

  // Skip the If condition OpCode
  if(
	 OpHeader->OpCode != EFI_IFR_SUPPRESS_IF_OP &&
	 OpHeader->OpCode != EFI_IFR_NO_SUBMIT_IF_OP &&
	 OpHeader->OpCode != EFI_IFR_INCONSISTENT_IF_OP &&
	 OpHeader->OpCode != EFI_IFR_GRAY_OUT_IF_OP &&
     OpHeader->OpCode != EFI_IFR_DISABLE_IF_OP
	 )
  {
	// This should not happen. The code should halt here.
	offset = 0;
	goto DONE;
  }

  // Skip the If opcode
  offset = OpHeader->Length;
  OpHeader = ( EFI_IFR_OP_HEADER * )(( UINT8 *)OpHeader + offset );

  do
  {
	switch( OpHeader->OpCode )
    {
	case EFI_IFR_END_OP:
	  inScope--;
	  break;
	default:
	  if(OpHeader->Scope)
		inScope++;
	  break;
	}
	offset += OpHeader->Length;
	OpHeader = ( EFI_IFR_OP_HEADER * )(( UINT8 *)OpHeader + OpHeader->Length );
  }while(inScope > 0);

DONE:
  return offset;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
