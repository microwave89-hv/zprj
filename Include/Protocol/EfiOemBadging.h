//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/EfiOemBadging.h 1     8/31/07 11:58a Felixp $
//
// $Revision: 1 $
//
// $Date: 8/31/07 11:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/EfiOemBadging.h $
// 
// 1     8/31/07 11:58a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EfiOemBadging.h
//
// Description:	OEM Badging protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __OEM_BADGING_PROTOCOL__H__
#define __OEM_BADGING_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_OEM_BADGING_PROTOCOL_GUID \
    { 0x170e13c0, 0xbf1b, 0x4218, 0x87, 0x1d, 0x2a, 0xbd, 0xc6, 0xf8, 0x87, 0xbc }

GUID_VARIABLE_DECLARATION(gEfiOEMBadgingProtocolGuid, EFI_OEM_BADGING_PROTOCOL_GUID);

typedef struct _EFI_OEM_BADGING_PROTOCOL EFI_OEM_BADGING_PROTOCOL;

typedef enum {
    EfiBadgingFormatBMP,
    EfiBadgingFormatJPEG,
    EfiBadgingFormatTIFF,
    EfiBadgingFormatGIF,
    EfiBadgingFormatUnknown
} EFI_BADGING_FORMAT;

typedef enum {
    EfiBadgingDisplayAttributeLeftTop,
    EfiBadgingDisplayAttributeCenterTop,
    EfiBadgingDisplayAttributeRightTop,
    EfiBadgingDisplayAttributeCenterRight,
    EfiBadgingDisplayAttributeRightBottom,
    EfiBadgingDisplayAttributeCenterBottom,
    EfiBadgingDisplayAttributeLeftBottom,
    EfiBadgingDisplayAttributeCenterLeft,
    EfiBadgingDisplayAttributeCenter,
    EfiBadgingDisplayAttributeCustomized
} EFI_BADGING_DISPLAY_ATTRIBUTE;

typedef EFI_STATUS (EFIAPI *EFI_BADGING_GET_IMAGE) (
    IN EFI_OEM_BADGING_PROTOCOL *This,
    IN OUT UINT32 *Instance, OUT EFI_BADGING_FORMAT *Format,
    OUT UINT8 **ImageData, OUT UINTN *ImageSize,
    OUT EFI_BADGING_DISPLAY_ATTRIBUTE *Attribute,
    OUT UINTN *CoordinateX, OUT UINTN *CoordinateY
);

struct _EFI_OEM_BADGING_PROTOCOL {
    EFI_BADGING_GET_IMAGE GetImage;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
