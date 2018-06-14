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
// $Header: /Alaska/SOURCE/Core/EDK/EdkLib.c 4     5/19/11 2:31p Artems $
//
// $Revision: 4 $
//
// $Date: 5/19/11 2:31p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/EdkLib.c $
// 
// 4     5/19/11 2:31p Artems
// EIP 60634: fixed bug in function IsHexDigit
// 
// 3     5/13/11 5:09p Artems
// Functions CopyMem and ZeroMem moved to EdkII library
// 
// 2     2/05/11 3:25p Artems
// Added EDK library functions CopyMem and ZeroMem
// 
// 1     5/19/06 11:28p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EdkLib.h
//
// Description:	This file contains implementation for EDK library routines.
// It's provided for EDK compatibility. 
// Whenever possible EDK routines implemented as a wrappers around AMI library routines.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiLib.h>
#include <Tiano.h>
#include <EfiCommonLib.h>
#include EFI_GUID_DEFINITION(StatusCodeDataTypeId)

UINTN ASPrint(
	OUT CHAR8 *Buffer, IN UINTN BufferSize,
	IN CONST CHAR8  *Format, ...
)
{
	va_list	ArgList = va_start(ArgList,Format);
	UINTN Ret = Sprintf_s_va_list(Buffer,BufferSize,(CHAR8*)Format,ArgList);
	va_end(ArgList);
	return Ret;
}

UINTN AvSPrint(
	OUT CHAR8 *StartOfBuffer, IN UINTN StrSize,
	IN CONST CHAR8 *Format, IN VA_LIST Marker
)
{
	return Sprintf_s_va_list(StartOfBuffer,StrSize,(CHAR8*)Format,Marker);
}

EFI_STATUS EfiInitializeCommonDriverLib (
  IN EFI_HANDLE   ImageHandle, IN VOID         *SystemTable
)
{
	return EFI_SUCCESS;
}

EFI_STATUS EfiCommonIoRead (
	IN UINT8 Width, IN UINTN Address,
	IN UINTN Count, IN OUT VOID *Buffer
)
{
	return IoRead(Width, Address, Count, Buffer);
}

EFI_STATUS EfiCommonIoWrite (
	IN UINT8 Width, IN UINTN Address,
	IN UINTN Count, IN OUT VOID *Buffer
)
{
	return IoWrite(Width, Address, Count, Buffer);
}
/*
EFI_STATUS EfiCommonPciRead (
	IN UINT8 Width, IN UINT64 Address,
	IN UINTN Count, IN OUT VOID *Buffer
)
{
	//TODO:
	return EFI_UNSUPPORTED;
}

EFI_STATUS EfiCommonPciWrite (
	IN UINT8 Width, IN UINT64 Address,
	IN UINTN Count, IN OUT VOID *Buffer
)
{
	//TODO:
	return EFI_UNSUPPORTED;
}
*/

BOOLEAN EfiCompareGuid (IN EFI_GUID *Guid1,IN EFI_GUID *Guid2)
{
	return !MemCmp(Guid1,Guid2,sizeof(EFI_GUID));
}

VOID EfiCommonLibSetMem(
	IN VOID   *Buffer, IN UINTN  Size, IN UINT8  Value
)
{
	MemSet(Buffer,Size,Value);
}

VOID EfiCommonLibCopyMem(
	IN VOID *Destination, IN VOID *Source,IN UINTN Length
)
{
	MemCpy(Destination,Source,Length);
}

/*
VOID
CopyMem (
  IN VOID   *Destination, IN VOID   *Source, IN UINTN  Length
)
{
  MemCpy (Destination, Source, Length);
}

VOID ZeroMem(IN VOID *Buffer, IN UINTN Size)
{
	MemSet(Buffer,Size,0);
}
*/

INTN EfiCompareMem (
	IN VOID *MemOne, IN VOID *MemTwo, IN UINTN Len
)
{
	return MemCmp(MemOne,MemTwo,Len);
}

VOID EfiCommonLibZeroMem(IN VOID *Buffer, IN UINTN Size)
{
	MemSet(Buffer,Size,0);
}

VOID* EfiConstructStatusCodeData (
	IN UINT16 DataSize, IN EFI_GUID *TypeGuid,
	IN OUT EFI_STATUS_CODE_DATA *Data
)
{
	if (!Data) return NULL;
	Data->HeaderSize=sizeof(EFI_STATUS_CODE_DATA);
	Data->Size=(UINT16)(DataSize - sizeof (EFI_STATUS_CODE_DATA));
	Data->Type=*TypeGuid;
	return Data + 1; 
}

EFI_STATUS EfiDebugVPrintWorker (
	IN UINTN ErrorLevel, IN CHAR8 *Format,
	IN  VA_LIST Marker, IN UINTN BufferSize,
	IN OUT VOID *Buffer
)
{
  UINTN                   Index;
  UINTN                   FormatStrLen;
  UINT64                  *Ptr;
  EFI_DEBUG_INFO          *EfiDebug;

  
  //
  // Build the type specific EFI_STATUS_CODE_DATA in order
  //

  //
  // Fill in EFI_STATUS_CODE_DATA to Buffer.
  //
  EfiDebug = (EFI_DEBUG_INFO *)EfiConstructStatusCodeData (
                                (UINT16)BufferSize, 
                                &gEfiStatusCodeDataTypeDebugGuid, 
                                Buffer
                                );

  //
  // Then EFI_DEBUG_INFO
  //
  EfiDebug->ErrorLevel = (UINT32)ErrorLevel;

  //
  // 256 byte mini Var Arg stack. That is followed by the format string.
  //
  for (Index = 0, Ptr = (UINT64 *)(EfiDebug + 1); Index < 12; Index++, Ptr++) {
    *Ptr = VA_ARG (Marker, UINT64);
  }

  //
  // Place Ascii Format string at the end 
  //
  FormatStrLen = EfiAsciiStrLen (Format) + 1;
  if (FormatStrLen > EFI_STATUS_CODE_DATA_MAX_SIZE) {
    //
    // Format too big to fit in our buffer, so do nothing.
    //
    return EFI_BUFFER_TOO_SMALL;
  } else {
    EfiCommonLibCopyMem (Ptr, Format, FormatStrLen);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EfiDebugAssertWorker (
  IN CHAR8                    *Filename,
  IN INTN                     LineNumber,
  IN CHAR8                    *Description,
  IN UINTN                    BufferSize,
  IN OUT VOID                 *Buffer
  )
{
  EFI_DEBUG_ASSERT_DATA   *AssertData;
  UINTN                   TotalSize;
  CHAR8                   *EndOfStr;

  //
  // Make sure it will all fit in the passed in buffer
  //
  TotalSize = sizeof (EFI_STATUS_CODE_DATA) + sizeof (EFI_DEBUG_ASSERT_DATA);
  TotalSize += EfiAsciiStrLen (Filename) + EfiAsciiStrLen (Description);
  if (TotalSize > BufferSize) {
    return EFI_BUFFER_TOO_SMALL;
  }

  //
  // Fill in EFI_STATUS_CODE_DATA
  //
  AssertData =  (EFI_DEBUG_ASSERT_DATA *)
                EfiConstructStatusCodeData (
                  (UINT16)(TotalSize - sizeof (EFI_STATUS_CODE_DATA)),
                  &gEfiStatusCodeDataTypeAssertGuid, 
                  Buffer
                  );

  //
  // Fill in EFI_DEBUG_ASSERT_DATA
  //
  AssertData->LineNumber = (UINT32)LineNumber;

  //
  // Copy Ascii FileName including NULL.
  //
  EndOfStr = EfiAsciiStrCpy ((CHAR8 *)(AssertData + 1), Filename);

  //
  // Copy Ascii Description 
  //
  EfiAsciiStrCpy (EndOfStr, Description);
  return EFI_SUCCESS;
}

BOOLEAN
ReportStatusCodeExtractAssertInfo (
  IN EFI_STATUS_CODE_TYPE     CodeType,
  IN EFI_STATUS_CODE_VALUE    Value,
  IN EFI_STATUS_CODE_DATA     *Data,
  OUT CHAR8                   **Filename,
  OUT CHAR8                   **Description,
  OUT UINT32                  *LineNumber
  )
{
  EFI_DEBUG_ASSERT_DATA   *AssertData;

  if (((CodeType & EFI_STATUS_CODE_TYPE_MASK) == EFI_ERROR_CODE) && 
        ((CodeType & EFI_STATUS_CODE_SEVERITY_MASK) == EFI_ERROR_UNRECOVERED)) {
    //
    // Assume if we have an uncontained unrecoverable error that the data hub
    // may not work. So we will print out data here. If we had an IPMI controller,
    // or error log we could wack the hardware here.
    //
    if ((Value & EFI_STATUS_CODE_OPERATION_MASK) == EFI_SW_EC_ILLEGAL_SOFTWARE_STATE && (Data != NULL)) {
      //
      // ASSERT (Expresion) - 
      // ExtendedData == FileName
      // Instance     == Line Nuber
      // NULL         == String of Expresion
      //
      AssertData = (EFI_DEBUG_ASSERT_DATA *)(Data + 1);
      *Filename = (CHAR8 *)(AssertData + 1);
      *Description = *Filename + EfiAsciiStrLen (*Filename) + 1;
      *LineNumber = AssertData->LineNumber;
      return TRUE;
    } 
  }
  return FALSE;
}

BOOLEAN
ReportStatusCodeExtractDebugInfo (
  IN EFI_STATUS_CODE_DATA     *Data,
  OUT UINT32                  *ErrorLevel,
  OUT VA_LIST                 *Marker,
  OUT CHAR8                   **Format
  )
{
  EFI_DEBUG_INFO      *DebugInfo;

  if ((Data == NULL) || (!EfiCompareGuid (&Data->Type, &gEfiStatusCodeDataTypeDebugGuid))) {
    return FALSE;
  }
  
  DebugInfo = (EFI_DEBUG_INFO *)(Data + 1);

  *ErrorLevel = DebugInfo->ErrorLevel;

  //
  // The first 12 * UINTN bytes of the string are really an 
  // arguement stack to support varargs on the Format string.
  //
  *Marker = (VA_LIST) (DebugInfo + 1);
  *Format = (CHAR8 *)(((UINT64 *)*Marker) + 12);

  return TRUE;
}

BOOLEAN
CodeTypeToPostCode (
  IN  EFI_STATUS_CODE_TYPE    CodeType,
  IN EFI_STATUS_CODE_VALUE    Value,
  OUT UINT8                   *PostCode
  )
{
  //TODO: reveiw
  if (((CodeType & EFI_STATUS_CODE_TYPE_MASK) == EFI_PROGRESS_CODE) ||
      ((CodeType & EFI_STATUS_CODE_TYPE_MASK)== EFI_ERROR_CODE)) {
    *PostCode = (UINT8) (((Value & EFI_STATUS_CODE_CLASS_MASK) >> 24) << 5);
    *PostCode |= (UINT8) (((Value & EFI_STATUS_CODE_SUBCLASS_MASK) >> 16) & 0x1f);
    return TRUE;
  }

  return FALSE;
}

UINT64 MultU64x32(IN UINT64 Multiplicand, IN UINTN Multiplier)
{
	return Mul64(Multiplicand,Multiplier);
}

UINT64 DivU64x32(
	IN UINT64 Dividend, IN UINTN Divisor,
	OUT UINTN *Remainder OPTIONAL
)
{
	return Div64(Dividend,Divisor,Remainder);
}

UINT64 RShiftU64(IN UINT64 Operand, IN UINTN Count)
{
	return Shr64(Operand,(UINT8)Count);
}

UINT64 LShiftU64(IN UINT64 Operand, IN UINTN Count)
{
	return Shl64(Operand,(UINT8)Count);
}

/*
TODO:
UINT64 
Power10U64 (
  IN UINT64   Operand,
  IN UINTN    Power
  )

UINT8
Log2 (
  IN UINT64   Operand
  )

UINT32
GetPowerOfTwo (
  IN  UINT32  Input
  )
*/

VOID EfiStrCpy (
	IN CHAR16 *Destination, IN CHAR16   *Source
)
{
	Wcscpy (Destination, Source);	
}

UINTN EfiStrLen (IN CHAR16   *String)
{
	return Wcslen(String);
}

UINTN EfiStrSize (IN CHAR16   *String)
{
	return (Wcslen(String)+1)*sizeof(CHAR16);
}

INTN EfiStrCmp (IN CHAR16 *String, IN CHAR16 *String2)
{
	return Wcscmp(String,String2);
}

VOID EfiStrCat (
	IN CHAR16 *Destination, IN CHAR16 *Source
)
{
	Wcscpy (Destination + Wcslen (Destination), Source);
}

UINTN EfiAsciiStrLen (IN CHAR8 *String)
{
	return Strlen(String);
}

CHAR8* EfiAsciiStrCpy (
	IN CHAR8 *Destination, IN CHAR8 *Source
)
{
	return Strcpy(Destination,Source);
}

UINTN EfiValueToHexStr (
	IN OUT CHAR16 *Buffer, IN UINT64 Value,
	IN UINTN Flags, IN UINTN Width
)
{
	//TODO: Flags
	return Swprintf(Buffer,L"%*lX",Width,Value);
}

UINTN EfiValueToString (
	IN OUT CHAR16 *Buffer, IN INT64 Value,
	IN UINTN Flags, IN UINTN Width
)
{
	//TODO: Flags
	return Swprintf(Buffer,L"%*ld",Width,Value);
}

BOOLEAN IsHexDigit (OUT UINT8 *Digit, IN CHAR16 Char)
{
	if (Char >= '0' && Char <= '9') {
        *Digit = (UINT8)(Char - '0');
        return TRUE;
    } else {
        Char &= 0xffdf;
        if (Char >= 'A' && Char <= 'F') {
            *Digit = (UINT8)(Char - 'A' + 10);
            return TRUE;
        }
    }
	return FALSE;
}

CHAR16 NibbleToHexChar (UINT8 Nibble)
{
	Nibble &= 0x0F;
	return (Nibble <= 9) ? Nibble + '0' : Nibble - 0xA + L'A';
}

EFI_STATUS HexStringToBuf (
	IN OUT UINT8 *Buf, IN OUT UINTN *Len,
	IN CHAR16 *Str, OUT UINTN *ConvertedStrLen OPTIONAL
)
{
  UINTN       HexCnt;
  UINTN       Idx;
  UINTN       BufferLength;
  UINT8       Digit;
  UINT8       Byte;

  //
  // Find out how many hex characters the string has.
  //
  for (Idx = 0, HexCnt = 0; IsHexDigit (&Digit, Str[Idx]); Idx++, HexCnt++);

  if (HexCnt == 0) {
    *Len = 0;
    return EFI_SUCCESS;
  }
  //
  // Two Unicode characters make up 1 buffer byte. Round up.
  //
  BufferLength = (HexCnt + 1) / 2; 

  //
  // Test if  buffer is passed enough.
  //
  if (BufferLength > (*Len)) {
    *Len = BufferLength;
    return EFI_BUFFER_TOO_SMALL;
  }

  *Len = BufferLength;

  for (Idx = 0; Idx < HexCnt; Idx++) {

    IsHexDigit (&Digit, Str[HexCnt - 1 - Idx]);

    //
    // For odd charaters, write the lower nibble for each buffer byte,
    // and for even characters, the upper nibble.
    //
    if ((Idx & 1) == 0) {
      Byte = Digit;
    } else {
      Byte = Buf[Idx / 2];
      Byte &= 0x0F;
      Byte |= Digit << 4;
    }

    Buf[Idx / 2] = Byte;
  }

  if (ConvertedStrLen != NULL) {
    *ConvertedStrLen = HexCnt;
  }

  return EFI_SUCCESS;
}


EFI_STATUS BufToHexString (
	IN OUT CHAR16 *Str, IN OUT UINTN *HexStringBufferLength,
	IN UINT8 *Buf, IN UINTN Len
)
{
  UINTN       Idx;
  UINT8       Byte;
  UINTN       StrLen;

  //
  // Make sure string is either passed or allocate enough.
  // It takes 2 Unicode characters (4 bytes) to represent 1 byte of the binary buffer.
  // Plus the Unicode termination character.
  //
  StrLen = Len * 2;
  if (StrLen > ((*HexStringBufferLength) - 1)) {
    *HexStringBufferLength = StrLen + 1;
    return EFI_BUFFER_TOO_SMALL;
  }

  *HexStringBufferLength = StrLen + 1;
  //
  // Ends the string.
  //
  Str[StrLen] = L'\0'; 

  for (Idx = 0; Idx < Len; Idx++) {

    Byte = Buf[Idx];
    Str[StrLen - 1 - Idx * 2] = NibbleToHexChar (Byte);
    Str[StrLen - 2 - Idx * 2] = NibbleToHexChar ((UINT8)(Byte >> 4));
  }

  return EFI_SUCCESS;
}

VOID EfiStrTrim (IN OUT CHAR16 *str, IN CHAR16 CharC)
{
  CHAR16  *p1;
  CHAR16  *p2;
  
  if (*str == 0) {
    return;
  }
  
  //
  // Trim off the leading and trailing characters c
  //
  for (p1 = str; *p1 && *p1 == CharC; p1++) {
    ;
  }
  
  p2 = str;
  if (p2 == p1) {
    while (*p1) {
      p2++;
      p1++;
    }
  } else {
    while (*p1) {    
    *p2 = *p1;    
    p1++;
    p2++;
    }
    *p2 = 0;
  }
  
  
  for (p1 = str + EfiStrLen(str) - 1; p1 >= str && *p1 == CharC; p1--) {
    ;
  }
  if  (p1 !=  str + EfiStrLen(str) - 1) { 
    *(p1 + 1) = 0;
  }
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