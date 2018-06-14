//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/DeferredImageLoad.h 1     5/13/11 4:40p Artems $
//
// $Revision: 1 $
//
// $Date: 5/13/11 4:40p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DeferredImageLoad.h $
// 
// 1     5/13/11 4:40p Artems
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<DeferredImageLoad.h>
//
// Description:	Deferred image load protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __DEFERRED_IMAGE_LOAD_H__
#define __DEFERRED_IMAGE_LOAD_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DEFERRED_IMAGE_LOAD_PROTOCOL_GUID \
  { 0x15853d7c, 0x3ddf, 0x43e0, 0xa1, 0xcb, 0xeb, 0xf8, 0x5b, 0x8f, 0x87, 0x2c }


GUID_VARIABLE_DECLARATION(gEfiDeferredImageLoadProtocolGuid, EFI_DEFERRED_IMAGE_LOAD_PROTOCOL_GUID);

typedef struct _EFI_DEFERRED_IMAGE_LOAD_PROTOCOL  EFI_DEFERRED_IMAGE_LOAD_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_DEFERRED_IMAGE_INFO)(
    IN  EFI_DEFERRED_IMAGE_LOAD_PROTOCOL  *This,
    IN  UINTN                             ImageIndex,
    OUT EFI_DEVICE_PATH_PROTOCOL          **ImageDevicePath,
    OUT VOID                              **Image,
    OUT UINTN                             *ImageSize,
    OUT BOOLEAN                           *BootOption
);

struct _EFI_DEFERRED_IMAGE_LOAD_PROTOCOL {
    EFI_DEFERRED_IMAGE_INFO  GetImageInfo;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************