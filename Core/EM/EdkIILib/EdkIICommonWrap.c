//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Core/EdkIICompLib/EdkIICommonWrap.c 2     5/13/11 5:46p Artems $
//
// $Revision: 2 $
//
// $Date: 5/13/11 5:46p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EdkIICompLib/EdkIICommonWrap.c $
// 
// 2     5/13/11 5:46p Artems
// Added functions CopyMem and ZeroMem
// 
// 1     5/05/11 5:06p Artems
// EdkII compatibility library
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  EdkIICommonWrap.c
//
//  Description:
//  
//
//<AMI_FHDR_END>
//*************************************************************************

#include <AmiDxeLib.h>
#include <EdkIICommon.h>

static EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;


INTN CompareMem(
    IN VOID  *DestinationBuffer,
    IN VOID  *SourceBuffer,
    IN UINTN Length)
{
    return MemCmp(DestinationBuffer, SourceBuffer, Length);
}


VOID* CopyMem(
    OUT VOID  *DestinationBuffer,
    IN  VOID  *SourceBuffer,
    IN UINTN  Length)
{
    MemCpy(DestinationBuffer, SourceBuffer, Length);
    return DestinationBuffer;
}

VOID* ZeroMem(
    OUT VOID  *Buffer,
    IN UINTN  Length)
{
    MemSet(Buffer, Length, 0);
    return Buffer;
}

BOOLEAN CompareGuid(
    IN EFI_GUID  *Guid1,
    IN EFI_GUID  *Guid2)
{
    return (guidcmp(Guid1, Guid2)) ? FALSE : TRUE;
}


VOID* AllocateRuntimePool(
    IN UINTN  AllocationSize)
{
    VOID *p;
    EFI_STATUS Status;

    Status = pBS->AllocatePool(EfiRuntimeServicesData, AllocationSize, &p);
    return (EFI_ERROR(Status)) ? NULL : p;
}

VOID* AllocatePool(
    IN UINTN  AllocationSize)
{
    VOID *p;
    EFI_STATUS Status;

    Status = pBS->AllocatePool(EfiBootServicesData, AllocationSize, &p);
    return (EFI_ERROR(Status)) ? NULL : p;
}

VOID* AllocateZeroPool(
    IN UINTN  AllocationSize)
{
    VOID *p;

    p = AllocatePool(AllocationSize);
    if(p != NULL)
        MemSet(p, AllocationSize, 0);

    return p;
}

VOID* AllocateCopyPool(
    IN UINTN  AllocationSize,
    IN VOID  *Buffer)
{
    VOID *p;

    p = AllocatePool(AllocationSize);
    if(p != NULL)
        MemCpy(p, Buffer, AllocationSize);

    return p;
}

VOID* ReallocatePool (
    IN UINTN  OldSize,
    IN UINTN  NewSize,
    IN VOID   *OldBuffer  OPTIONAL)
{
    VOID *p;

    p = AllocateZeroPool(NewSize);
    if(p != NULL && OldBuffer != NULL) {
        MemCpy(p, OldBuffer, MIN(OldSize, NewSize));
        pBS->FreePool(OldBuffer);
    }

    return p;
}

VOID FreePool(
    IN VOID   *Buffer)
{
    pBS->FreePool(Buffer);
}

EFI_STATUS EfiGetSystemConfigurationTable(
    IN  EFI_GUID  *TableGuid,
    OUT VOID      **Table)
{
    *Table = GetEfiConfigurationTable(pST, TableGuid);
    return (*Table == NULL) ? EFI_NOT_FOUND : EFI_SUCCESS;
}

UINTN GetDevicePathSize(
    IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath)
{
    return DPLength(DevicePath);
}

EFI_DEVICE_PATH_PROTOCOL* DevicePathFromHandle(
    IN EFI_HANDLE Handle)
{
    EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
    EFI_STATUS                Status;

    Status = pBS->HandleProtocol(
                  Handle,
                  &gEfiDevicePathProtocolGuid,
                  (VOID *) &DevicePath);
    return (EFI_ERROR(Status)) ? NULL : DevicePath;
}

UINTN UnicodeSPrint (
    OUT CHAR16  *StartOfBuffer,
    IN  UINTN   BufferSize,
    IN  CHAR16  *FormatString,
    ...)
{
    UINTN n;
	va_list	ArgList = va_start(ArgList, FormatString);
	n = Swprintf_s_va_list(StartOfBuffer, BufferSize, FormatString, ArgList);
	va_end(ArgList);
	return n;
}

UINTN UnicodeVSPrint (
    OUT CHAR16  *StartOfBuffer,
    IN  UINTN   BufferSize,
    IN  CHAR16  *FormatString,
    IN  VA_LIST Marker)
{
    UINTN n;
	n = Swprintf_s_va_list(StartOfBuffer, BufferSize, FormatString, Marker);
	return n;
}

EFI_GUID* CopyGuid (
    OUT EFI_GUID  *DestinationGuid,
    IN  EFI_GUID  *SourceGuid)
{
    *DestinationGuid = *SourceGuid;
    return DestinationGuid;
}

VOID InitEfiPointers(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable)
{
	pBS = SystemTable->BootServices;
	pRS = SystemTable->RuntimeServices;
    gBS = pBS;
    gRT = pRS;
    gST = SystemTable;
}

UINTN AsciiStrLen (
    IN CHAR8 *String)
{
  UINTN Length;

  for (Length = 0; *String != '\0'; String++, Length++);

  return Length;
}

UINTN StrLen (
    IN CHAR16 *String)
{
  UINTN Length;

  for (Length = 0; *String != L'\0'; String++, Length++);

  return Length;
}

UINTN StrSize (
    IN CHAR16 *String)
{
  UINTN Size;

  for (Size = 2; *String != L'\0'; String++, Size += 2);

  return Size;
}

INTN StrCmp (
  IN CHAR16 *FirstString,
  IN CHAR16 *SecondString
)
{
    return Wcscmp(FirstString, SecondString);
}

VOID* SetMem16 (
    OUT VOID   *Buffer,
    IN UINTN   Length,
    IN UINT16  Value)
{
    UINTN i;

    Length /= 2;    //we have input length in bytes

    for(i = 0; i < Length; i++)
        *((UINT16 *)Buffer + i) = Value;
    return Buffer;
}

CHAR16* StrCpy (
    OUT CHAR16 *Destination,
    IN  CHAR16 *Source)
{
  CHAR16 *ReturnValue;

  ReturnValue = Destination;
  while (*Source != 0) {
    *(Destination++) = *(Source++);
  }
  *Destination = 0;
  return ReturnValue;
}

CHAR16* StrCat (
  IN OUT  CHAR16 *Destination,
  IN      CHAR16 *Source)
{
  StrCpy (Destination + StrLen (Destination), Source);

  return Destination;
}

VOID* GetEfiGlobalVariable (
    IN CHAR16 *Name)
{
    EFI_STATUS Status;
    VOID *Var = 0;
    UINTN VarSize;

    Status = GetEfiVariable(Name, &gEfiGlobalVariableGuid, NULL, &VarSize, &Var);
    return (EFI_ERROR(Status)) ? NULL : Var;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
