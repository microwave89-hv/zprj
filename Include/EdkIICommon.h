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
// $Header: /Alaska/SOURCE/Core/EdkIICompLib/EdkIICommon.h 2     5/13/11 5:50p Artems $
//
// $Revision: 2 $
//
// $Date: 5/13/11 5:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EdkIICompLib/EdkIICommon.h $
// 
// 2     5/13/11 5:50p Artems
// Renamed function EfiCompareGuid with native EdkII CompareGuid
// 
// 1     5/05/11 5:04p Artems
// EdkII compatibility library headers
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<EdkIICommon.h>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EDKII_COMMON__H__
#define __EDKII_COMMON__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Protocol/DevicePath.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextOut.h>

#ifndef END_DEVICE_PATH_TYPE
#define END_DEVICE_PATH_TYPE                 0x7f
#endif

#define END_ENTIRE_DEVICE_PATH_SUBTYPE       0xFF
#define EFI_DP_TYPE_MASK                     0x7F
#define EFI_DP_TYPE_UNPACKED                 0x80
#define END_INSTANCE_DEVICE_PATH_SUBTYPE     0x01

#define DevicePathType(a)           ( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)        ( (a)->SubType )
#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )

#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define IsDevicePathEndSubType(a)   ( (a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )
#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))

#define SIGNATURE_16(A,B)             ((A) | (B<<8))
#define SIGNATURE_32(A,B,C,D)         (SIGNATURE_16(A,B)     | (SIGNATURE_16(C,D)     << 16))
#define SIGNATURE_64(A,B,C,D,E,F,G,H) (SIGNATURE_32(A,B,C,D) | ((UINT64)(SIGNATURE_32(E,F,G,H)) << 32))

#define MIN(a,b)   (((a) < (b)) ? (a) : (b))
#define MAX(a,b)   (((a) > (b)) ? (a) : (b))

#define CHAR_NULL             0x0000
#define CHAR_BACKSPACE        0x0008
#define CHAR_TAB              0x0009
#define CHAR_LINEFEED         0x000A
#define CHAR_CARRIAGE_RETURN  0x000D

#define SCAN_NULL EFI_SCAN_NULL
#define SCAN_UP         EFI_SCAN_UP
#define SCAN_DOWN       EFI_SCAN_DN
#define SCAN_RIGHT      EFI_SCAN_RIGHT
#define SCAN_LEFT       EFI_SCAN_LEFT
#define SCAN_HOME       EFI_SCAN_HOME
#define SCAN_END        EFI_SCAN_END
#define SCAN_INSERT     EFI_SCAN_INS
#define SCAN_DELETE     EFI_SCAN_DEL
#define SCAN_PAGE_UP    EFI_SCAN_PGUP
#define SCAN_PAGE_DOWN  EFI_SCAN_PGDN
#define SCAN_F1         EFI_SCAN_F1
#define SCAN_F2         EFI_SCAN_F2
#define SCAN_F3         EFI_SCAN_F3
#define SCAN_F4         EFI_SCAN_F4
#define SCAN_F5         EFI_SCAN_F5
#define SCAN_F6         EFI_SCAN_F6
#define SCAN_F7         EFI_SCAN_F7
#define SCAN_F8         EFI_SCAN_F8
#define SCAN_F9         EFI_SCAN_F9
#define SCAN_F10        EFI_SCAN_F10
#define SCAN_F11        EFI_SCAN_F11
#define SCAN_F12        EFI_SCAN_F12
#define SCAN_ESC        EFI_SCAN_ESC


#define _EFI_INT_SIZE_OF(n) ((sizeof (n) + sizeof (UINTN) - 1) &~(sizeof (UINTN) - 1))

#ifndef VA_START

typedef CHAR8 *VA_LIST;
#define VA_START(ap, v) (ap = (VA_LIST) & (v) + _EFI_INT_SIZE_OF (v))
#define VA_ARG(ap, t)   (*(t *) ((ap += _EFI_INT_SIZE_OF (t)) - _EFI_INT_SIZE_OF (t)))
#define VA_END(ap)      (ap = (VA_LIST) 0)

#endif


EFI_BOOT_SERVICES		*gBS;
EFI_RUNTIME_SERVICES	*gRT;
EFI_SYSTEM_TABLE        *gST;

INTN CompareMem(
    IN VOID  *DestinationBuffer,
    IN VOID  *SourceBuffer,
    IN UINTN Length
);


VOID* CopyMem (
    OUT VOID  *DestinationBuffer,
    IN  VOID  *SourceBuffer,
    IN UINTN  Length
);

VOID* SetMem16 (
    OUT VOID   *Buffer,
    IN UINTN   Length,
    IN UINT16  Value
);


BOOLEAN CompareGuid(
    IN EFI_GUID  *Guid1,
    IN EFI_GUID  *Guid2
);


VOID* AllocateCopyPool(
    IN UINTN       AllocationSize,
    IN CONST VOID  *Buffer
);

VOID* AllocateZeroPool(
    IN UINTN  AllocationSize
);

VOID* AllocateRuntimePool(
    IN UINTN  AllocationSize
);

VOID* AllocatePool(
    IN UINTN  AllocationSize
);

VOID* ReallocatePool (
    IN UINTN  OldSize,
    IN UINTN  NewSize,
    IN VOID   *OldBuffer  OPTIONAL
);

VOID FreePool(
    IN VOID   *Buffer
);

EFI_DEVICE_PATH_PROTOCOL* DevicePathFromHandle(
    IN EFI_HANDLE Handle
);

UINTN GetDevicePathSize(
    IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
);

UINTN UnicodeSPrint (
    OUT CHAR16  *StartOfBuffer,
    IN  UINTN   BufferSize,
    IN  CHAR16  *FormatString,
    ...
);

UINTN UnicodeVSPrint (
    OUT CHAR16  *StartOfBuffer,
    IN  UINTN   BufferSize,
    IN  CHAR16  *FormatString,
    IN  VA_LIST Marker
);

EFI_STATUS EfiGetSystemConfigurationTable(
    IN  EFI_GUID  *TableGuid,
    OUT VOID      **Table
);


VOID* ZeroMem (
    OUT VOID  *Buffer,
    IN UINTN  Length
);


EFI_GUID* CopyGuid (
    OUT EFI_GUID  *DestinationGuid,
    IN  EFI_GUID  *SourceGuid
);

VOID InitEfiPointers(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
);

VOID
EFIAPI
CreatePopUp (
  IN  UINTN          Attribute,                
  OUT EFI_INPUT_KEY  *Key,      OPTIONAL
  ...
  );

UINTN StrLen (
  IN CHAR16              *String
);

INTN StrCmp (
  IN CHAR16 *FirstString,
  IN CHAR16 *SecondString
);

UINTN StrSize (
  IN CHAR16              *String
);

CHAR16* StrCpy (
    OUT CHAR16 *Destination,
    IN  CHAR16 *Source
);

CHAR16* StrCat (
    IN OUT  CHAR16 *Destination,
    IN      CHAR16 *Source
);

UINTN AsciiStrLen (
    IN CHAR8 *String
);

CHAR16* ConvertDeviceNodeToText (
    IN CONST EFI_DEVICE_PATH_PROTOCOL  *DeviceNode,
    IN BOOLEAN                         DisplayOnly,
    IN BOOLEAN                         AllowShortcuts
);

CHAR16* ConvertDevicePathToText (
    IN CONST EFI_DEVICE_PATH_PROTOCOL   *DevicePath,
    IN BOOLEAN                          DisplayOnly,
    IN BOOLEAN                          AllowShortcuts
);

VOID* GetEfiGlobalVariable (
    IN CHAR16 *Name
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