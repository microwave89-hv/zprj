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
// $Header: /Alaska/SOURCE/Core/EDK/GUID/DebugImageInfoTable.h 2     10/07/06 10:23a Felixp $
//
// $Revision: 2 $
//
// $Date: 10/07/06 10:23a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/GUID/DebugImageInfoTable.h $
// 
// 2     10/07/06 10:23a Felixp
// UIEFI2.0 support.
// Updated to EDK 20060904
// 
// 1     5/19/06 11:28p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DebugImageInfoTable.h
//
// Description:	Debug Image Info TableDXE
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_DEBUG_IMAGE_INFO_TABLE_GUID__H__
#define __EFI_DEBUG_IMAGE_INFO_TABLE_GUID__H__
#ifdef __cplusplus
extern "C" {
#endif
#define EFI_DEBUG_IMAGE_INFO_TABLE_GUID \
  { 0x49152e77,0x1ada,0x4764,0xb7,0xa2,0x7a,0xfe,0xfe,0xd9,0x5e,0x8b }

GUID_VARIABLE_DECLARATION(gEfiDebugImageInfoTableGuid, EFI_DEBUG_IMAGE_INFO_TABLE_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include<Protocol/LoadedImage.h>

#define EFI_DEBUG_IMAGE_INFO_UPDATE_IN_PROGRESS 0x01
#define EFI_DEBUG_IMAGE_INFO_TABLE_MODIFIED     0x02
#define EFI_DEBUG_IMAGE_INFO_TYPE_NORMAL        0x01

typedef struct {
  UINT64                Signature;
  EFI_PHYSICAL_ADDRESS  EfiSystemTableBase;
  UINT32                Crc32;
} EFI_SYSTEM_TABLE_POINTER;

typedef struct {
  UINTN                     ImageInfoType;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImageProtocolInstance;
  EFI_HANDLE                *ImageHandle;
} EFI_DEBUG_IMAGE_INFO_NORMAL;

typedef union {
  UINTN                       *ImageInfoType;
  EFI_DEBUG_IMAGE_INFO_NORMAL *NormalImage;
} EFI_DEBUG_IMAGE_INFO;

typedef struct {
  volatile UINT32       UpdateStatus;
  UINT32                TableSize;
  EFI_DEBUG_IMAGE_INFO  *EfiDebugImageInfoTable;
} EFI_DEBUG_IMAGE_INFO_TABLE_HEADER;
/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
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